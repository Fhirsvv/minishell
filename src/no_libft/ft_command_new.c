/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:02:21 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:10:43 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*ft_command_new(char **args, char *c_path)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	new->args = ft_array_duplicate(args);
	new->comand_path = c_path;
	new->next = NULL;

	//printf("nuevo token:\n%s\n%d\n", new->content, new->symbol);
	return (new);
}