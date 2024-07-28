/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:23:00 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/28 21:39:55 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_quotes(const char *prompt)
{
	char	quote_char;
	int		quotes;
	int		i;

	quote_char = '\0';
	quotes = 0;
	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			if (quote_char == '\0')
			{
				quote_char = prompt[i];
				quotes++;
			}
			else if (quote_char == prompt[i])
			{
				quote_char = '\0';
				quotes++;
			}
		}
		i++;
	}
	if(quotes % 2 == 0)
		return (0);
	printf("comillas mal\n");
	return (1);
}

void add_token_and_free(char *start_q, char *end_q, char *prompt, t_myshell *tshell)
{
	if (start_q)
	{
		char *buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
		printf("%s\n", buff);
		free(buff);
	}
}

int	token_type(char *str)
{
	int	type;

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
