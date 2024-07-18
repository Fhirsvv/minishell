/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:42:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/18 12:53:48 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

//gcc src/main.c -o mini -lreadline

int main()
{
	char *prompt;

	while (1)
	{
		prompt = readline("MINISHELL-> ");
		printf("%s\n", prompt);
		free(prompt);
	}
	
	return 0;
}