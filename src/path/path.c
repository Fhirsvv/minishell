/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:24:33 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/11 23:41:39 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(t_myshell *tshell)
{
	int		i;
	char	*envp_path;

	i = 0;
	envp_path = NULL;
	while (tshell->environ[i])
	{
		if (ft_strncmp("PATH", tshell->environ[i], 4) == 0)
		{
			envp_path = tshell->environ[i];
			return (envp_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *path, char *cmd)
{
	char	**possible_path;
	char	*cmd_route;
	char	*aux_route;
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strtrim(path, "PATH=");
	possible_path = ft_split(aux, ':');
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (possible_path[++i])
	{
		aux_route = ft_strjoin(possible_path[i], "/");
		cmd_route = ft_strjoin(aux_route, cmd);
		if (access(cmd_route, F_OK) != -1 && access(cmd_route, X_OK) != -1)
			break ;
		else
		{
			ft_free2(aux_route, cmd_route);
			cmd_route = NULL;
		}
	}
	free (aux);
	return (cmd_route);
}
