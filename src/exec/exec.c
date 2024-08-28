/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/20 11:32:30 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//todo: rehacer todo el exec ppara funcionar con s_commands xd

static int execute_command(t_command *command, char **environ)
{
    if (execve(command->comand_path, command->args, environ) == -1)
    {
        perror("Error en execve");
        exit(ERROR_INVALID_PARAMETER);
    }
    return 0;
}

// Función para manejar la ejecución de comandos con múltiples pipes
void execute_pipeline(t_myshell *shell)
{
    t_command *cmd = shell->comands;
    int pipe_fd[2], prev_fd = -1;
    pid_t pid;
    
    while (cmd)
    {
        if (cmd->next && cmd->next->comand_path)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("Error en pipe");
                exit(ERROR_INVALID_PARAMETER);
            }
        }
        pid = fork();
        if (pid < 0)
        {
            perror("Error en fork");
            exit(ERROR_INVALID_PARAMETER);
        }
        if (pid == 0) // Proceso hijo
        {
            // Si hay un comando anterior, conectar la entrada estándar al extremo de lectura del pipe anterior
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO); // Conectar entrada estándar al extremo de lectura del pipe anterior
                close(prev_fd);
            }
            // Si hay un siguiente comando, redirigir la salida estándar al extremo de escritura del nuevo pipe
            if (cmd->next && cmd->next->comand_path)
            {
                close(pipe_fd[0]); // Cerrar el extremo de lectura del pipe en el hijo
                dup2(pipe_fd[1], STDOUT_FILENO); // Redirigir salida estándar al pipe
                close(pipe_fd[1]);
            }
            // Ejecutar el comando actual
            execute_command(cmd, shell->environ);
        }
        else // Proceso padre
        {
            // El padre cierra los descriptores usados
            if (prev_fd != -1)
                close(prev_fd);
            if (cmd->next && cmd->next->comand_path)
                close(pipe_fd[1]); // Cerrar el extremo de escritura del pipe en el padre
            // Actualizar el descriptor previo para el siguiente ciclo
            prev_fd = pipe_fd[0];
            // Esperar a que el proceso hijo termine si es el último comando
            if (!cmd->next)
                waitpid(pid, NULL, 0);
        }
        // Avanzar al siguiente comando
        cmd = cmd->next;
    }
}
