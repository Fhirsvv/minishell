/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/16 21:34:58 by ecortes-         ###   ########.fr       */
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

//https://www.youtube.com/watch?v=6xbLgZpOBi8
//https://www.youtube.com/watch?v=NkfIUo_Qq4c
static void	exec_pipe(t_comand *cmd)
{
	//fd[0] = read end -- fd[1] = write end
	int fd[2];
	int pids[2];

	if (pipe(fd) < 0)
		perror("error pipe\n");
	pids[0] = fork();
	
	//algo con fds->fd_in y fd_out
	if(cmd->fds->fd_in < 0)
		dup2(cmd->fds->fd_in, STDIN_FILENO);
	if (pids[0] < 0)
		perror("errore algo 1\n");
	if (pids[0] == 0)
	{
		close(fd[0]);
		//dup2(fd[1], cmd->fds->fd_out);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		//exec
		close(fd[1]);
	}
	if (cmd->next->next) //o aqui solo añadir el dup2(stdin_fileno, cmd->next->next->fds.fd_in)
	{
		pids[1] = fork();
		if (pids[1] < 0)
			perror("error algo 2\n");
		if (pids[1] == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			//exec
			//todoooooooooo
		}
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

void	exec(t_myshell *tshell)
{
	t_comand	*cmd;
	int		*flds;
	int i;
	
	i = 0;
	//inicio aqui u nproceso para que aunque solo haya
	//un comando no cierre el comando actual
	flds = ft_calloc(tshell->pipes_count + 1, sizeof(int));
	cmd = tshell->comands;
	while (cmd)
	{
		if (tshell->pipes_count == 0)
			ft_exec_one(cmd);
		else
			exec_pipe(cmd);
		cmd = cmd->next;
	}
	
	free(flds);
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