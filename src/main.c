/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/20 21:28:01 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>


//gcc src/main.c -o mini -lreadline
void loop()
{
	char *prompt;
	
	while (1)
	{
		prompt = readline("MINISHELLL$ ");
		/*if (strlen(prompt) > 0)
			add_history(prompt);*/
		
	}
}

int main (int argc, char **argv, char **environ)
{
	(void *)argv;
	
	return 0;
}