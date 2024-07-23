/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/23 15:42:54 by ecortes-         ###   ########.fr       */
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
    char *start_q = NULL;
    char *end_q = NULL;
    char *buff = NULL;
    int i = 0;
    bool in_quotes = false;
    char quote_char = '\0';

    while (prompt[i]) {
        if (prompt[i] == ' ' && !in_quotes) {
            if (start_q != NULL) {
                end_q = &prompt[i];
                buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
                ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
                printf("TOKEN CONTENT=%s\n", buff);
                free(buff);
                start_q = NULL;
            }
        } else if (prompt[i] == '\'' || prompt[i] == '"') {
            if (in_quotes && prompt[i] == quote_char) {
                in_quotes = false;
                quote_char = '\0';
            } else if (!in_quotes) {
                in_quotes = true;
                quote_char = prompt[i];
                if (start_q == NULL) {
                    start_q = &prompt[i + 1];
                }
            }
        } else {
            if (start_q == NULL) {
                start_q = &prompt[i];
            }
        }
        i++;
    }

    if (start_q != NULL) {
        end_q = &prompt[i];
        buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
        ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
        printf("TOKEN CONTENT=%s\n", buff);
        free(buff);
    }
}
