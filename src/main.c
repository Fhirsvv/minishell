/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:38:20 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/23 00:09:13 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int token_type(char *str)
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
	return type;
}
		
void new_tokkenice(char *prompt, t_myshell *tshell)
{
    int i;
    char *aux;
    char *substr;

    aux = prompt;
    while ((aux = ft_strchr(aux, ' ')) != NULL)
    {
        i = aux - prompt;
        substr = ft_substr(prompt, 0, i);
        ft_tokenadd_back(&tshell->tokens, ft_token_new(substr, token_type(substr)));
        free(substr);
        aux++; // Mover aux al siguiente carácter después del espacio
        prompt = aux; // Mover prompt para comenzar desde la nueva posición
    }
    // Añadir el último token después del último espacio
    if (*prompt != '\0') {
        substr = ft_strdup(prompt);
        ft_tokenadd_back(&tshell->tokens, ft_token_new(substr, token_type(substr)));
        free(substr);
    }
}

void loop(t_myshell *tshell)
{
	while (1)
	{
		tshell->prompt = readline("MINISHELL$ ");
		/*if (strlen(tshell->prompt) > 0)
			add_history(tshell->prompt);*/
		//split_pipe(tshell->prompt, tshell);
		new_tokkenice(tshell->prompt, tshell);
	}
}

void init_tshell(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;	
}
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