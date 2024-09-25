/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/09/24 18:12:39 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// todo: rehacer todo el exec ppara funcionar con s_commands xd

static int execute_command(t_command *command, char **environ)
{
	if (execve(command->comand_path, command->args, environ) == -1)
	{
		perror("");
		//exit(ERROR_INVALID_PARAMETER);
	}
	return 0;
}
void main_exec(t_myshell *tshell)
{
	t_command *cmd;
	pid_t pid;

	cmd = tshell->comands;
	while (cmd)
	{
		//is_builtin(tshell, cmd);
		pid = fork();
		if (pid < 0)
		{
			perror("Error en fork");
			exit(ERROR_INVALID_PARAMETER);
		}
		if (pid == 0) // hijo
		{
			execute_command(cmd, tshell->environ);
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
void is_builtin(t_myshell *tshell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	if (ft_strcmp(cmd->args[0], "ls") == 0)
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
	if (ft_strcmp(cmd->args[0], "export") == 0)
	if (ft_strcmp(cmd->args[0], "unset") == 0)
	if (ft_strcmp(cmd->args[0], "env") == 0)
	if (ft_strcmp(cmd->args[0], "exit") == 0)
}
*/