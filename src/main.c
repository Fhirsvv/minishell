/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 21:18:10 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void tokenice(char *str, t_myshell *tshell)
{
	int type;
	
	type = 0;
	if(strcmp(str, "|") == 0)
		type = PIPE;
	else if(strcmp(str, ">") == 0)
		type = REDIR_D;
	else if(strcmp(str, ">>") == 0)
		type = DOBLE_REDIR_D;
	else if(strcmp(str, "<") == 0)
		type = REDIR_I;
	else if(strcmp(str, "<<") == 0)
		type = HERE_DOC;
	else
		type = WORD;
	t_token *aux = ft_token_new(str, type);
	ft_lstadd_back(&tshell->tokens, aux);
}

void split_pipe(char *prompt, t_myshell *tshell)
{
	char **split_pipes;
	char **split_spaces;
	int i;

	i = 0;
	split_pipes = ft_split(prompt, '|');
	while (split_pipes[i])
	{
		split_spaces = ft_split(split_pipes[i], ' ');
		//aqui algo para las comillas puede ser
		tokenice(split_spaces[i], tshell);
		i++;
	}
	
}

void loop(t_myshell *tshell)
{	
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		/*if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);*/
		split_pipe(tshell->prompt, tshell);
	}
}

void init_tshell(t_myshell *myshell)
{
	myshell->tokens = NULL;
	myshell->environ = NULL;
	myshell->prompt = NULL;	
}
int main (int argc, char **argv, char **environ)
{
	t_myshell tshell;
	//int i = 0;
	
	(void)argc;
	(void)argv;
	(void)environ;
	/*while (environ[i++])
		tshell.environ[i] = strdup(environ[i]);*/
	init_tshell(&tshell);
	loop(&tshell);
	
	exit(1);
	//free_myshell(&tshell);
	return 0;
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
}