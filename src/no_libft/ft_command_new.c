/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:02:21 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/11 23:53:41 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void init_fds(t_fds **fds)
{
	*fds = malloc(sizeof(t_fds));
	if (!(*fds))
		return ;
	(*fds)->apend_file = NULL;
	(*fds)->input_file = NULL;
	(*fds)->output_file = NULL;
	(*fds)->fd_in = -1;
    (*fds)->fd_out = -1;
    (*fds)->stdin_backup = dup(STDIN_FILENO);
    (*fds)->stdout_backup = dup(STDOUT_FILENO);
}

t_comand	*ft_command_new(char **args, char *c_path)
{
	t_comand	*new;

	new = malloc(sizeof(t_comand));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	new->args = ft_array_duplicate(args);
	new->comand_path = c_path;
	init_fds(&new->fds);
	new->next = NULL;
	return (new);
}
