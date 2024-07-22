/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:38:46 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 17:54:18 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back(t_token **tmyshell, t_token *new)
{
	t_token	*node;

	if (*tmyshell == NULL)
		*tmyshell = new;
	else
	{
		node = *tmyshell;
		while (node->next != NULL)
		{
			node = node->next;
		}
		node->next = new;
	}
}