/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:19:58 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/05 13:35:23 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief GET THE VAR CONTENT TO SUBSTITUTE IN THE PROMPT AND SUBSTITUTE IT
/// @param post_dollar WHAT IS AFTER THE DOLAR SIGN IN THE PROMPT (VAR NAME)
/// @param in_path PART OF THE ENVIRON WHERE POST_DOLLAR IS FOUND
/// @param token CURRENT TOKEN WE ARE WORKING WITH
/// @param tshell GENERAL STRUCT
int get_char_to_expand(char *post_dollar, char *in_path, t_token *token)
{
	char *aux;
	char *new_prompt;
	int i;

	i = 0;
	aux = NULL;
	new_prompt = NULL;
	while(token->content[i])
	{
		aux = new_prompt;
		if(token->content[i] != '$')
			new_prompt = ft_strjoin(aux, &token->content[i]);
		else
		{
			new_prompt = ft_strjoin(aux + 1, ft_strtrim(in_path, ft_strjoin(post_dollar, "=")));
			i += ft_strlen(ft_strjoin("$", post_dollar));
		}
		i++;
		if(aux)
			free(aux);
		if(new_prompt == NULL)
			return (0);
	}
	return(1);
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
	while(auxstr[i] != ' ' && auxstr[i] != '|' && auxstr[i] != '<' && auxstr[i] != '>' && auxstr[i] != ')' && auxstr[i] != '(' && auxstr[i] != '$' && auxstr[i])
		i++;
	aux2 = ft_substr(auxstr, 0, i);
	printf("despues de substr\n");
	if(!aux2)
		return (0);
	i = 0;
	while (tshell->environ[i])
	{
		if (ft_strncmp(aux2, tshell->environ[i], ft_strlen(aux2)) == 0)
		{
			auxstr = tshell->environ[i];
			break;
		}
		i++;
	}	
	return(get_char_to_expand(aux2, auxstr, token));
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
		if((aux->symbol == D_QUOTE || aux->symbol == WORD ) && ft_strchr(aux->content, '$'))
			error = get_part_expand(aux, tshell);
		if(error == 0) //diferente maenjo de errores segun lo que devuelva
			printf("error en expandern\n");
		aux = aux->next;
	}
}