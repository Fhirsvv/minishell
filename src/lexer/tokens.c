/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/23 15:31:23 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int token_type(char *str)
{
	int type;

	type = 0;
	if (strcmp(str, "|") == 0)
		type = PIPE;
	else if (strcmp(str, ">") == 0)
		type = REDIR_D;
	else if (strcmp(str, ">>") == 0)
		type = DOBLE_REDIR_D;
	else if (strcmp(str, "<") == 0)
		type = REDIR_I;
	else if (strcmp(str, "<<") == 0)
		type = HERE_DOC;
	else if(str[0] == '\"')
		type = D_QUOTE;
	else
		type = WORD;
	return type;
}

void new_tokkenice(char *prompt, t_myshell *tshell)
{
	int len;
	char *aux;
	char *substr;

	aux = prompt;
	while ((aux = ft_strchr(aux, ' ')) != NULL)
	{
		len = aux - prompt;
		substr = ft_substr(prompt, 0, len);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(substr, token_type(substr)));
		free(substr);
		aux++;
		prompt = aux;
	}
	if (*prompt != '\0')
	{
		substr = ft_strdup(prompt);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(substr, token_type(substr)));
		free(substr);
	}
}

void tokens_and_quotes(char *prompt, t_myshell *tshell)
{
	char *start_q;
	char *end_q;
	char *buff;
	int i = 0;

	end_q = NULL;
	start_q = prompt;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
		{
			if (end_q == NULL)
				end_q = &prompt[i];
		}
		else if (prompt[i] == '\'')
		{
			while (end_q == NULL)
			{
				while (prompt[i] != '\'')
					i++;
				if (prompt[i] == '\'' && prompt[i - 1] != '\\')
					end_q = &prompt[i];
				i++;
			}
		}
		if (start_q != NULL && end_q != NULL)
		{
			buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
			ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
			printf("TOKKEN CONTENT=%s\n", buff);
			free(buff);
			start_q = end_q;
			end_q = NULL;
		}
		i++;
	}
}
