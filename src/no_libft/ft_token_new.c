/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:27:57 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:04:59 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_token_new(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	new->content = strdup(str);
	new->symbol = type;
	new->next = NULL;

	//printf("nuevo token:\n%s\n%d\n", new->content, new->symbol);
	return (new);
}
