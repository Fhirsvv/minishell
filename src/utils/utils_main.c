/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:33:10 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/28 11:16:45 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_myshell(t_myshell *tshell)
{
	free_loop(tshell);
	int i = 0;
	while (tshell->environ[i])
	{
		free(tshell->environ[i]);
		i++;
	}
	free(tshell->environ);
}

const char *get_token_type_name(int symbol)
{
	switch (symbol)
	{
	case PIPE:
		return "PIPE";
	case REDIR_D:
		return "REDIR_D";
	case DOBLE_REDIR_D:
		return "DOBLE_REDIR_D";
	case REDIR_I:
		return "REDIR_I";
	case HERE_DOC:
		return "HERE_DOC";
	case WORD:
		return "WORD";
	case D_QUOTE:
		return "D_QUOTE";
	case S_QUOTE:
		return "S_QUOTE";
	default:
		return "UNKNOWN";
	}
}

void print_tokens(t_myshell *tshell)
{
	t_token *current_token;

	current_token = tshell->tokens;
	while (current_token)
	{
		printf("Token: %s, Type: %s\n", current_token->content,
			   get_token_type_name(current_token->symbol));
		current_token = current_token->next;
	}
}

void print_args(t_myshell *tshell)
{
    t_command *aux;
    int i;
    
	i = 0;
    aux = tshell->comands;
	while(aux)
	{
		i++;
		aux = aux->next;
	}
	printf("HAY %d comandos\n", i);
	aux = tshell->comands;
    while (aux)
    {
        i = 0;
        while (aux->args && aux->args[i])
        {
			printf("ARGS->%s\n", aux->args[i]);
			if(aux->comand_path)
            	printf("PATH->%s\n", aux->comand_path);
            i++;
        }
        printf("----------------\n");  // Añadir separador entre comandos
        aux = aux->next;
    }
}


void free_loop(t_myshell *tshell)
{
	t_token *next;
	t_command *aux;

	if(tshell->prompt)
		free(tshell->prompt);
	while (tshell->tokens)
	{
		next = tshell->tokens->next;
		free(tshell->tokens->content);
		free(tshell->tokens);
		tshell->tokens = next;
	}
	tshell->tokens = NULL;
	while(tshell->comands)
	{
		aux = tshell->comands->next;
		free_arr(tshell->comands->args);
		//free(tshell->comands->comand_path);
		free(tshell->comands);
		tshell->comands = aux;
	}
	tshell->comands = NULL;
}

int how_many_finds(char *str, int c)
{
	char *aux;
	int count;

	count = 0;
	aux = str;
	while(1)
	{
		aux = ft_strchr(aux, c);
		if(!aux)
			return (count);
		aux++;
		count++;
	}
	return (count);
}
