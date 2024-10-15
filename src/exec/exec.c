/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/15 19:36:02 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_command(t_comand *command, char **environ)
{
	if (execve(command->comand_path, command->args, environ) == -1)
	{
		perror("");
		//exit(ERROR_INVALID_PARAMETER);
	}
	return 0;
}
void	exec(t_myshell *tshell)
{
	t_comand	*cmd;
	int		*pid;
	
	pid = ft_calloc(tshell->pipes_count, sizeof(int));
	cmd = tshell->comands;
	while (cmd)
	{
		                    
		cmd = cmd->next;
	}
	
	free(pid);
}
void ns(t_myshell *tsh)
{
	while (cmd)
	{
		//is_builtin(tshell, cmd);
		pid[i] = fork();
		if (pid < 0)
		{
			perror("Error en fork");
			exit(ERROR_INVALID_PARAMETER);
		}
		if (pid == 0) // hijo
		{
			execute_command(cmd, tsh->environ);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			return;
	}
}
/*
int	comand_exec(t_myshell *tshell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	else if (ft_strcmp(cmd->args[0], "ls") == 0)
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	else if (ft_strcmp(cmd->args[0], "env") == 0)
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	
}
*/