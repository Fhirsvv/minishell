/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandadd_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:11:33 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:12:12 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_commandadd_back(t_command **lst, t_command *new)
{
	t_command	*node;

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