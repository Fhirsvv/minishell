/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/16 15:16:11 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//TODO:  cuidado con dobles comillas y expander y espacios
void print_args(t_myshell *tshell);

void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);
		if (count_quotes(tshell->prompt) == SUCCESS)
			tokens_and_quotes(tshell->prompt, tshell);
		expander_main(tshell);
		build_comands_main(tshell);
		print_tokens(tshell);
		print_args(tshell);
		free_loop(tshell);
	}
}

int main(int argc, char **argv, char **environ)
{
	t_myshell tshell;

	(void)argv;
	if (argc != 1)
	{
		write(1, "MINISHELL does not accept arguments\n", 37);
		return (ERROR_INVALID_PARAMETER);
	}
	init_tshell(&tshell, environ);
	loop(&tshell);

	exit(1);
	// free_myshell(&tshell);
	return 0;
}
