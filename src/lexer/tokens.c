/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/27 22:49:28 by ecortes-         ###   ########.fr       */
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
	else if (str[0] == '\"')
		type = D_QUOTE;
	else
		type = WORD;
	return type;
}

static void add_token_and_free(char *start_q, char *end_q, char *prompt, t_myshell *tshell)
{
	if (start_q)
	{
		char *buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
		printf("%s\n", buff);
		free(buff);
	}
}
void tokens_and_quotes(char *prompt, t_myshell *tshell)
{
	char *start_q;
	int i;
	char quote_char;

	start_q = NULL;
	i = 0;
	quote_char = '\0';
	while (prompt[i])
	{
		if (prompt[i] == ' ' && quote_char == '\0' && start_q)
		{
				add_token_and_free(start_q, &prompt[i], prompt, tshell);
				start_q = NULL;
		}
		else if (prompt[i] == '\'' || prompt[i] == '"')
		{
			if (quote_char == prompt[i])
			{
				add_token_and_free(start_q, &prompt[i], prompt, tshell);
				start_q = NULL;
				quote_char = '\0';
			}
			else if (quote_char == '\0')
			{
				quote_char = prompt[i];
				if (start_q)
				{
					add_token_and_free(start_q, &prompt[i], prompt, tshell);
				}
				start_q = &prompt[i + 1];
			}
		}
		else if (prompt[i] == '|')
		{
			if (quote_char == '\0')
			{
				if (start_q)
				{
					add_token_and_free(start_q, &prompt[i], prompt, tshell);
					start_q = NULL;
				}
				add_token_and_free(&prompt[i], &prompt[i + 1], prompt, tshell);
			}
			else
			{
				if (!start_q)
					start_q = &prompt[i];
			}
		}
		else
		{
			if (!start_q)
				start_q = &prompt[i];
		}
		i++;
	}
	if (start_q)
		add_token_and_free(start_q, &prompt[i], prompt, tshell);
}
