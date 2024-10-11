/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:23:00 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/12 00:18:23 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_last_token_symbol(t_myshell *tshell, int new_symbol)
{
	t_token	*current;

	current = tshell->tokens;
	if (tshell == NULL || tshell->tokens == NULL)
	{
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->symbol = new_symbol;
}

int	token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return(PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return(REDIR_D);
	else if (ft_strcmp(str, ">>") == 0)
		return(DOBLE_REDIR_D);
	else if (ft_strcmp(str, "<") == 0)
		return(REDIR_I);
	else if (ft_strcmp(str, "<<") == 0)
		return(HERE_DOC);
	else if (str[0] == '"')
		return(D_QUOTE);
	else if (str[0] == '\'')
		return(S_QUOTE);
	else
		return(WORD);
}

void	add_token_and_free(char *start_q, char *end_q, char *prompt, t_myshell *tshell)
{
	if (start_q)
	{
		char *buff = ft_substr(prompt, start_q - prompt, end_q - start_q);
		ft_tokenadd_back(&tshell->tokens, ft_token_new(buff, token_type(buff)));
		ft_free(buff);
	}
}


void split_various_dolar(t_myshell *tshell)
{
	t_token	*aux;
	t_token	*new;
	t_token	*next;
	char	**arr;
	int		i;

	aux = tshell->tokens;
	while (aux)
	{
		next = aux->next;
		if ((aux->symbol == WORD || aux->symbol == D_QUOTE)
			&& how_many_finds(aux->content, '$') > 1)
		{
			arr = ft_split(aux->content, '$');
			if (!arr)
				return;
			new = ft_token_new(ft_strjoin("$", arr[0]), WORD);
			ft_tokensubstitute(&tshell->tokens, new, aux);
			i = 1;
			ft_add_after(tshell, arr, new, &i);
		}
		aux = next;
	}
}
