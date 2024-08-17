/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:19:58 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/16 18:11:32 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*substr_part_expand(char *auxstr)
{
	int	i;

	i = 0;
	if(!auxstr)
		return (NULL);
	while(auxstr[i] && auxstr[i] != ' ' && auxstr[i] != '\n' && auxstr[i] != '	' )
		i++;
	return(ft_substr(auxstr, 1, i - 1));
}

/// @brief SUBSITITUTE THE VAR CONTENT IN TOKENS->D_QUOTE
/// @param prompt ORIGINAL PROMPT
/// @param old_str WHAT WE WANT TO CHANGE
/// @param new_str WHAT WE ARE GOING TO CHANGE OLD_STR
/// @return THE PROMPT CHANGED
char	*replace_substr(char *prompt, char *old_str, char *new_str)
{
	int		i;
	char	*aux;
	char	*aux2;

	i = 0;
	aux = NULL;
	aux2 = NULL;
	if (!prompt || !old_str || !new_str)
		return (NULL);
	while(prompt[i] != '$' && prompt[i])
		i++;
	if(i != 0)
	{
		aux = ft_substr(prompt, 0, i);
		aux2 = ft_strjoin(aux, new_str);
		if(!aux || !aux2)
			return (NULL);
		free(aux);
		if(&prompt[i + ft_strlen(old_str)])
			aux = ft_strjoin(aux2, &prompt[i + ft_strlen(old_str)]);
		free(aux2);
	}
	else
		aux = ft_strjoin(new_str, &prompt[ft_strlen(old_str)]);
	return(aux);
}

/// @brief GET THE VAR CONTENT TO SUBSTITUTE IN THE PROMPT AND SUBSTITUTE IT
/// @param post_dollar WHAT IS AFTER THE DOLAR SIGN IN THE PROMPT (VAR NAME)
/// @param in_path PART OF THE ENVIRON WHERE POST_DOLLAR IS FOUND
/// @param token CURRENT TOKEN WE ARE WORKING WITH
/// @param tshell GENERAL STRUCT
int	get_char_to_expand(char *post_dollar, char *in_path, t_token *token)
{
	char	*aux;
	char	*aux_content;

	if (!in_path)
		return (2);
	aux = NULL;
	aux = ft_semi_strtrim(in_path, ft_strjoin(post_dollar, "=")); //aqui cambaiir el trim creo
	if (!aux)
		return (ERROR_MEMORY);
	aux_content = token->content;
	token->content = replace_substr(token->content, ft_strjoin("$", post_dollar), aux);
	free(aux_content);
	if(!token->content)
		return (ERROR_GENERIC);
	free(post_dollar);
	return (SUCCESS);
}

/// @brief GET THE VAR NAME AFTER DE $ IN THE PROMPT
/// @param token TOKEN WICH IS MARKED AS D_QUOTE
/// @param tshell GENERAL STRUCT
int	get_part_expand(t_token *token, t_myshell *tshell)
{
	char	*auxstr;
	char	*aux2;
	int		i;

	i = 0;
	aux2 = NULL;
	auxstr = ft_strchr(token->content, '$');
	auxstr = substr_part_expand(auxstr);
	i = 0;
	while (tshell->environ[i])
	{
		if (ft_strncmp(ft_strjoin(auxstr, "="), tshell->environ[i], ft_strlen(auxstr) + 1) == 0)
		{
			aux2 = tshell->environ[i];
			break;
		}
		i++;
	}
	return (get_char_to_expand(auxstr, aux2, token));
}

/// @brief MAIN FUNCTION TO EXPAND THE PROMPTS
/// @param tshell GENERAL STRUCT
int	expander_main(t_myshell *tshell)
{
	int		error;
	t_token	*aux;

	aux = tshell->tokens;
	while (aux)
	{
		if ((aux->symbol == D_QUOTE || aux->symbol == WORD) && ft_strchr(aux->content, '$') && ft_strcmp(aux->content, "$") != 0)
		{
			error = get_part_expand(aux, tshell);
			if (error != SUCCESS) // diferente maenjo de errores segun lo que devuelva
				return(ERROR_GENERIC);
		}
		aux = aux->next;
	}
	return(SUCCESS);
}
