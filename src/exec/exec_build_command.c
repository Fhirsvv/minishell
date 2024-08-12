/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:56:03 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/12 20:14:00 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int build_comands_main(t_myshell *tshell)
{
	int error;
	t_token *aux;
	
	aux = tshell->tokens;
	while(aux)
	{
		if(aux->symbol == WORD || aux->symbol == D_QUOTE || aux->symbol == S_QUOTE)
		{
			t_token *aa = aux;
			error = new_command(tshell, aux); //aux no se actualiza dentro de new_command
			if(aa == aux)
				printf("mismo token aaaaaaaaaaaaaaaaaaaaaa\n");
			if(error != SUCCESS)
				return (error);
		}
		else
		{
			error = new_command_symbols(tshell, aux);
			if(error != SUCCESS)
				return (error);
		}
		aux = aux->next;
	}
	return(SUCCESS);    
}

int new_command_symbols(t_myshell *tshell, t_token *aux)
{
	t_command *new;
	char **arr;

	arr = NULL;
	arr = add_to_matrix(arr, aux->content);
	if(!arr)
		return (ERROR_MEMORY);
	new = ft_command_new(arr, NULL);
	ft_commandadd_back(&tshell->comands, new);
	free_arr(arr);
	return(SUCCESS);
}

int new_command(t_myshell *tshell, t_token *aux)
{
	char **arr;
	char **buff;
	t_command *new;

	arr = NULL;
	buff = NULL;
	while(aux && (aux->symbol == WORD || aux->symbol == D_QUOTE ||
			aux->symbol == S_QUOTE))
	{
		arr = add_to_matrix(buff, aux->content);
		if(!arr)
		{
			free_arr(buff);
			return (ERROR_MEMORY);
		}
		free(buff);
		buff = arr;
		aux = aux->next;
	}
	if(arr)
	{
		new = ft_command_new(arr, get_cmd_path(tshell->path, arr[0]));
		ft_commandadd_back(&tshell->comands, new);
		free_arr(arr);
	}
	return (SUCCESS);
}

char **add_to_matrix(char **arr, char *new)
{
	char **aux;
	size_t i;

	i = 0;
	if(!arr)
	{
		aux = ft_calloc(i + 2, sizeof(char *));
		aux[0] = ft_strdup(new);
		return (aux);
	}
	while(arr[i])
			i++;
	aux = ft_calloc(i + 2, sizeof(char *));
	if (!aux)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		aux[i] = ft_strdup(arr[i]);
		if (!aux[i])
		{
			free_arr(aux);
			return (aux);
		}
		i++;
	}
	aux[i] = ft_strdup(new);
	if (!aux[i])
	{
		free_arr(aux);
		return (aux);
	}
	aux[i + 1] = NULL;
	return (aux);
}
