/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:42:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/18 13:13:15 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//gcc src/main.c -o mini -lreadline

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


//environ is initialized as a pointer to an array of character pointers to the environment strings.
int main(int argc, char** argv, char** environ)
{
	char *prompt;

	(void *)argv;
	(void)argc;
	(void *)environ;
	while (1)
	{
		prompt = readline("MINISHELL-> ");
		printf("%s\n", prompt);
		free(prompt);
	}
	
	return 0;
}