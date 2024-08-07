/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:33:10 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:08:23 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int init_tshell(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
	return(SUCCESS);
}

void free_myshell(t_myshell *tshell)
{
	free_loop(tshell);
	int i = 0;
	while (tshell->environ[i])
	{
		free(tshell->environ[i]);
		i++;
	}
	free(tshell->environ);
}

const char *get_token_type_name(int symbol)
{
	switch (symbol)
	{
	case PIPE:
		return "PIPE";
	case REDIR_D:
		return "REDIR_D";
	case DOBLE_REDIR_D:
		return "DOBLE_REDIR_D";
	case REDIR_I:
		return "REDIR_I";
	case HERE_DOC:
		return "HERE_DOC";
	case WORD:
		return "WORD";
	case D_QUOTE:
		return "D_QUOTE";
	case S_QUOTE:
		return "S_QUOTE";
	default:
		return "UNKNOWN";
	}
}

void print_tokens(t_myshell *tshell)
{
	t_token *current_token;

	current_token = tshell->tokens;
	while (current_token)
	{
		printf("Token: %s, Type: %s\n", current_token->content,
			   get_token_type_name(current_token->symbol));
		current_token = current_token->next;
	}
}

void free_loop(t_myshell *tshell)
{
	t_token *next;

	while (tshell->tokens)
	{
		next = tshell->tokens->next;
		free(tshell->tokens->content);
		free(tshell->tokens);
		tshell->tokens = next;
	}
	tshell->tokens = NULL;
}