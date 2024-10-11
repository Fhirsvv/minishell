/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_comands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:29:40 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/12 00:06:03 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_comand(t_comand **cmds, t_comand *rm)
{
	t_comand	*aux;
	t_comand	*to_rm;
	
	if (*cmds == rm)
	{
		to_rm = *cmds;
		*cmds = (*cmds)->next;
	}
	else
	{
		aux = *cmds;
		while (aux->next != rm)
			aux = aux->next;
		to_rm = aux->next;
		aux->next = aux->next->next;
	}
	ft_free(to_rm->comand_path);
	free_fds(to_rm->fds);
	free_arr(to_rm->args);
	free(to_rm);
	return ;
}

static int	is_symbol_setup(t_comand *next)
{
	if (!ft_strcmp(next->args[0], ">>") || !ft_strcmp(next->args[0], ">")
		|| !ft_strcmp(next->args[0], "<"))
		return (0);
	return (1);
}

void	setup_comands(t_comand **cmds)
{
	t_comand	*aux;
	t_comand	*next;

	aux = *cmds;
	next = aux->next;
	while (next)
	{
		if (!is_symbol_setup(next) && next->next) //esto repensarlo pero esta es la idea
		{ 
			if (!ft_strcmp(next->args[0], ">>"))
					aux->fds->apend_file = ft_strdup(next->next->args[0]);
			else if (!ft_strcmp(next->args[0], ">"))
					aux->fds->output_file = ft_strdup(next->next->args[0]);
			else if (!ft_strcmp(next->args[0], "<"))
					aux->fds->input_file = ft_strdup(next->next->args[0]);
			(remove_comand(cmds, next->next), remove_comand(cmds, next));
		}
		else if (!is_symbol_setup(next))
			perror("syntax error near unexpected token `newline'\n"); //TODO: hacer algo para el manejo de errores
		if (!aux->next)
			return ;
		aux = aux->next;
		next = aux->next;
	}
}
	