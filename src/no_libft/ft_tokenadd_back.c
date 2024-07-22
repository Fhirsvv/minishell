/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:38:46 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 18:16:12 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
		{
			node = node->next;
		}
		node->next = new;
	}
}