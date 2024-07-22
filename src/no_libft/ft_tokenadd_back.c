/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:38:46 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 21:12:03 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

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
