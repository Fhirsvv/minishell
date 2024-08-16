/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:23:00 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/15 15:13:31 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void update_last_token_symbol(t_myshell *tshell, int new_symbol)
{
	t_token *current;

	current = tshell->tokens;
	if (tshell == NULL || tshell->tokens == NULL)
	{
		printf("No tokens to update.\n");
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->symbol = new_symbol;
}

int count_quotes(const char *prompt)
{
	char quote_char;
	int quotes;
	int i;

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
	if (quotes % 2 == 0)
		return (SUCCESS);
	printf("comillas mal\n");
	return (ERROR_GENERIC);
}

void add_token_and_free(char *start_q, char *end_q, char *prompt, t_myshell *tshell)
{
	if (start_q)
	{
		char *buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
		// printf("%s\n", buff);
		free(buff);
	}
}

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
	else if (str[0] == '"')
		type = D_QUOTE;
	else if(str[0] == '\'')
		type = S_QUOTE;
	else
		type = WORD;
	return type;
}

void split_various_dolar(t_myshell *tshell)
{
    t_token *aux;
    t_token *new;
    t_token *next;
    char **arr;
    int i;

    aux = tshell->tokens;
    while(aux)
    {
        // Store the next node before making any changes to the current node
        next = aux->next;
        
        if((aux->symbol == WORD || aux->symbol == D_QUOTE) && how_many_finds(aux->content, '$') > 1)
        {
            arr = ft_split(aux->content, '$');
            if(!arr)
                return;

            new = ft_token_new(ft_strjoin("$",arr[0]), WORD);
            ft_tokensubstitute(&tshell->tokens, new, aux);
            printf("After tokensubstitute\n");

            // Add subsequent tokens after the newly substituted node
            i = 1;
            while(arr[i])
            {
                ft_tokenadd_after(&tshell->tokens, ft_token_new(ft_strjoin("$",arr[i]), WORD), new);
                new = new->next; // Move new to the last added token to continue chaining
                i++;
            }
        }
        
        // Move to the next node
        aux = next;
    }
}

