/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/27 19:35:09 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void new_parser(char *promtp, t_token *tokens);

int main (int argc, char **argv, char **environ)
{
	t_myshell tshell;
	
	(void)argv;
	if(argc != 1)
	{
		write(1, "MINISHELL does not accept arguments\n", 37);
		return (0);
	}
	init_tshell(&tshell, environ);
	loop(&tshell);
	
	exit(1);
	//free_myshell(&tshell);
	return 0;
}
void print_tokens(t_token *token)
{
	t_token *aux = token;

	while(aux->next)
	{
		printf("tokens=");
		printf("%s\n", aux->content);
		aux = aux->next;
	}
	
}
void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		/*if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);*/
		//new_tokkenice(tshell->prompt, tshell);
		tokens_and_quotes(tshell->prompt, tshell);
		//exec_things(tshell);
		//print_tokens(tshell->tokens);
		
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
	t_token	*next;

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
