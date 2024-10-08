/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/09/24 22:05:15 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int init_tshell(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
	myshell->comands = NULL;
	return(SUCCESS);
}

void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		if (tshell->prompt == NULL)
		{
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
		if (count_quotes(tshell->prompt) == SUCCESS)
			tokens_and_quotes(tshell->prompt, tshell);
		if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);
		expander_main(tshell);
		build_comands_main(tshell);
		//print_tokens(tshell);
		print_args(tshell);
		main_exec(tshell);
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
	main_signals();
	init_tshell(&tshell, environ);
	loop(&tshell);

	exit(1);
	// free_myshell(&tshell);
	return 0;
}
