/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:19:58 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/05 23:03:48 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief SUBSITITUTE THE VAR CONTENT IN TOKENS->D_QUOTE
/// @param prompt ORIGINAL PROMPT
/// @param old_str WHAT WE WANT TO CHANGE
/// @param new_str WHAT WE ARE GOING TO CHANGE OLD_STR
/// @return THE PROMPT CHANGED
char *replace_substr(char *prompt, char *old_str, char *new_str)
{
	int i;
	char *aux;
	char *aux2;

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
		aux = ft_strjoin(aux2, &prompt[i + ft_strlen(old_str) + 1]);
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
int get_char_to_expand(char *post_dollar, char *in_path, t_token *token)
{
	char *aux;
	char *aux_content;

	if (!in_path)
		return (2);
	aux = NULL;
	aux = ft_strtrim(in_path, ft_strjoin(post_dollar, "="));
	if (!aux)
		return (0);
	aux_content = token->content;
	token->content = replace_substr(token->content, ft_strjoin("$", post_dollar), aux);
	free(aux_content);
	if(!token->content)
		return (0);
	return 1;
}

/// @brief GET THE VAR NAME AFTER DE $ IN THE PROMPT
/// @param token TOKEN WICH IS MARKED AS D_QUOTE
/// @param tshell GENERAL STRUCT
int get_part_expand(t_token *token, t_myshell *tshell)
{
	char *auxstr;
	char *aux2;
	int i;

	i = 0;
	aux2 = NULL;
	auxstr = ft_strchr(token->content, '$');
	auxstr++;
	i = 0;
	while (tshell->environ[i])
	{
		if (ft_strncmp(auxstr, tshell->environ[i], ft_strlen(auxstr)) == 0)
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
void expander_main(t_myshell *tshell)
{
	int error;
	t_token *aux;

	aux = tshell->tokens;
	while (aux)
	{
		if ((aux->symbol == D_QUOTE || aux->symbol == WORD) && ft_strchr(aux->content, '$'))
		{
			error = get_part_expand(aux, tshell);
			if (error != 1) // diferente maenjo de errores segun lo que devuelva
				printf("error en expandern\n");
		}
		aux = aux->next;
	}
}