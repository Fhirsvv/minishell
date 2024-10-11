/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:56:03 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/12 00:03:19 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**copy_and_add(char **arr, char **aux, char *new)
{
	int	i;
	
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

static char	**add_to_matrix(char **arr, char *new)
{
	char	**aux;
	size_t	i;

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
	return (copy_and_add(arr, aux, new));
}

static int	new_command_symbols(t_myshell *tshell, t_token *aux)
{
	t_comand	*new;
	char		**arr;

	arr = NULL;
	arr = add_to_matrix(arr, aux->content);
	if(!arr)
		return (ERROR_MEMORY);
	new = ft_command_new(arr, NULL);
	ft_commandadd_back(&tshell->comands, new);
	free_arr(arr);
	return(SUCCESS);
}

 static t_token	*new_command(t_myshell *tshell, t_token *aux)
{
	char		**arr;
	char		**buff;

	arr = NULL;
	buff = NULL;
	while(aux && (aux->symbol == WORD || aux->symbol == D_QUOTE ||
			aux->symbol == S_QUOTE))
	{
		arr = add_to_matrix(buff, aux->content);
		if(!arr)
		{
			free_arr(buff);
			return (NULL);
		}
		free(buff);
		buff = arr;
		aux = aux->next;
	}
	if(arr)
	{
		ft_commandadd_back(&tshell->comands,
			ft_command_new(arr, get_cmd_path(tshell->path, arr[0])));
		free_arr(arr);
	}
	return (aux);
}


int	comands(t_myshell *tshell)
{
	int		error;
	t_token	*aux;
	
	aux = tshell->tokens;
	while(aux)
	{
		if(aux->symbol == WORD || aux->symbol == D_QUOTE || aux->symbol == S_QUOTE)
		{
			aux = new_command(tshell, aux);
			if(!aux)
				return(ERROR_MEMORY);
		}
		if(!(aux->symbol == WORD || aux->symbol == D_QUOTE || aux->symbol == S_QUOTE))
		{
			error = new_command_symbols(tshell, aux);
			if(error != SUCCESS)
				return (error);
		}
		aux = aux->next;
	}
	return(SUCCESS);
}
