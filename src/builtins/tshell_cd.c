/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:43:45 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/12 00:14:51 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void my_cd(t_comand *cmd)
{
	if (!cmd->args[1])
	{
		printf("No valid argument\n");
		return;
	}
	if (chdir(cmd->args[1]) != 0)
		perror("cd");
}
