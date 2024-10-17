/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/17 11:06:46 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
	myshell->comands = NULL;
	myshell->err_msg = NULL;
	return(SUCCESS);
}

int	main(int argc, char **argv, char **environ)
{
	t_myshell	tshell;

	(void)argv;
	if (argc != 1)
	{
		write(1, "MINISHELL does not accept arguments\n", 37);
		return (ERROR_INVALID_PARAMETER);
	}
	signals();
	init(&tshell, environ);
	loop(&tshell);
	free_minishell(&tshell, NULL);
	return (0);
}
