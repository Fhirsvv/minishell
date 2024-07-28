/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/28 23:16:07 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_space(char *prompt, int *i, char **start_q, char quote_char, t_myshell *tshell)
{
	if (prompt[*i] == ' ' && quote_char == '\0' && *start_q)
	{
		add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
		*start_q = NULL;
	}
}

void handle_quotes(char *prompt, int *i, char *quote_char, char **start_q, t_myshell *tshell)
{
	if (prompt[*i] == '\'' || prompt[*i] == '"')
	{
		if (*quote_char == prompt[*i])
		{
			add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
			update_last_token_symbol(tshell, token_type(quote_char));
			*start_q = NULL;
			*quote_char = '\0';
		}
		else if (*quote_char == '\0')
		{
			*quote_char = prompt[*i];
			if (*start_q)
				add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
			*start_q = &prompt[*i + 1];
		}
	}
}

void handle_pipe(char *prompt, int *i, char *quote_char, char **start_q, t_myshell *tshell)
{
	if (prompt[*i] == '|')
	{
		if (*quote_char == '\0')
		{
			if (*start_q)
			{
				add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
				*start_q = NULL;
			}
			add_token_and_free(&prompt[*i], &prompt[*i + 1], prompt, tshell);
		}
		else if (!*start_q)
			*start_q = &prompt[*i];
	}
}

void handle_redirection(char *prompt, int *i, char **start_q, char quote_char, t_myshell *tshell)
{
	if (quote_char == '\0')
	{
		if (prompt[*i] == '<' || prompt[*i] == '>')
		{
			if ((prompt[*i] == '<' && prompt[*i + 1] == '<') ||
				(prompt[*i] == '>' && prompt[*i + 1] == '>'))
			{
				if (*start_q)
				{
					add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
					*start_q = NULL;
				}
				add_token_and_free(&prompt[*i], &prompt[*i + 2], prompt, tshell);
				*i += 1;
			}
			else
			{
				if (*start_q)
				{
					add_token_and_free(*start_q, &prompt[*i], prompt, tshell);
					*start_q = NULL;
				}
				add_token_and_free(&prompt[*i], &prompt[*i + 1], prompt, tshell);
			}
		}
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
		handle_space(prompt, &i, &start_q, quote_char, tshell);
		handle_quotes(prompt, &i, &quote_char, &start_q, tshell);
		handle_pipe(prompt, &i, &quote_char, &start_q, tshell);
		handle_redirection(prompt, &i, &start_q, quote_char, tshell);
        if (prompt[i] != ' ' && prompt[i] != '\'' && prompt[i] != '"' && prompt[i] != '|' &&
            prompt[i] != '<' && prompt[i] != '>' && !start_q)
            start_q = &prompt[i];
		i++;
	}
	if (start_q)
		add_token_and_free(start_q, &prompt[i], prompt, tshell);
}
