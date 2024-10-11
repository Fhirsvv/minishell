/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandadd_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:11:33 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/11 23:54:26 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_commandadd_back(t_comand **lst, t_comand *new)
{
	t_comand	*node;

	if(new == NULL)
	{
		printf("new vacio\n");
		return;
	}
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next)
		{
			node = node->next;
		}
		node->next = new;
	}
}