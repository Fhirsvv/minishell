/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/04 13:23:13 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char *get_token_type_name(int symbol) {
    switch (symbol) {
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
        default:
            return "UNKNOWN";
    }
}

// Función para imprimir la lista de tokens
void print_tokens(t_myshell *tshell) {
    t_token *current_token = tshell->tokens;

    while (current_token) {
        printf("Token: %s, Type: %s\n", 
               current_token->content,
               get_token_type_name(current_token->symbol));
        current_token = current_token->next;
    }
}

int main(int argc, char **argv, char **environ)
{
	t_myshell tshell;

	(void)argv;
	if (argc != 1)
	{
		write(1, "MINISHELL does not accept arguments\n", 37);
		return (0);
	}
	init_tshell(&tshell, environ);
	loop(&tshell);

	exit(1);
	// free_myshell(&tshell);
	return 0;
}

void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		/*if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);*/
		if (count_quotes(tshell->prompt) == 0)
			tokens_and_quotes(tshell->prompt, tshell);
		expander_main(tshell);
			print_tokens(tshell);

		free(tshell->prompt);
	}
}

void init_tshell(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
}

void free_myshell(t_myshell *tshell)
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
	int i = 0;
	while (tshell->environ[i])
	{
		free(tshell->environ[i]);
		i++;
	}
	free(tshell->environ);
}
