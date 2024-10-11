/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 23:13:45 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/12 00:14:33 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free2(char *arr1, char *arr2)
{
	free(arr1);
	free(arr2);
}

void	free_tokens(t_token **tk)
{
	t_token	*next;

	while (*tk)
	{
		next = (*tk)->next;
		ft_free((*tk)->content);
		free((*tk));
		*tk = next;
	}
	*tk = NULL;
}

void	free_comands(t_comand **cmds)
{
	t_comand	*aux;

	while(*cmds)
	{
		aux = (*cmds)->next;
		free_arr((*cmds)->args);
		ft_free((*cmds)->comand_path);
		free_fds((*cmds)->fds);
		free(*cmds);
		*cmds = aux;
	}
}

void	free_fds(t_fds *fds)
{
	if (!fds)
		return;
	ft_free(fds->apend_file);
	ft_free(fds->input_file);
	ft_free(fds->output_file);
	free(fds);
	fds = NULL;
}
