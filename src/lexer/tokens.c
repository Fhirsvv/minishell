/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/28 21:29:16 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
