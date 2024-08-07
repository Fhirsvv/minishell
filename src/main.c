/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 12:57:13 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		/*if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);*/
		if (count_quotes(tshell->prompt) == SUCCESS)
			tokens_and_quotes(tshell->prompt, tshell);
		expander_main(tshell);
		print_tokens(tshell);

		free(tshell->prompt);
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
