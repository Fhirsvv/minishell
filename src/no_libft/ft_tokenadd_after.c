/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_after.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:09:33 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/14 20:44:24 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_tokenadd_after(t_token **lst, t_token *new, t_token *wh)
{
	t_token *node;
	t_token *aux;

	if (new == NULL || lst == NULL || wh == NULL)
		return;

	node = *lst;
	while (node != NULL)
	{
		if (node == wh)
		{
			aux = node->next;
			node->next = new;
			new->next = aux;
			return;
		}
		node = node->next;
	}
}
