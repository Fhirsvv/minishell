/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/16 18:03:48 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//todo: rehacer todo el exec ppara funcionar con s_commands xd

static int real_exec(char *path, char **argv, char **environ)
{
    execve(path, argv, environ);
    return(ERROR_INVALID_PARAMETER);
}

static void ft_exec(char *path, char **environ, t_token *token)
{
    int count = 0;
    char **arr;
    t_token *aux = token;

    if (token == NULL)
    {
        fprintf(stderr, "Error: token es nulo\n");
        return;
    }

    while (aux && aux->symbol == WORD)
    {
        count++;
        aux = aux->next;
    }

    aux = token;
    arr = malloc(sizeof(char *) * (count + 1));
    if (arr == NULL)
    {
        perror("malloc");
        return;
    }

    count = 0;
    while (aux && aux->symbol == WORD)
    {
        arr[count] = ft_strdup(aux->content);
        if (arr[count] == NULL)
        {
            while (count > 0)
                free(arr[--count]);
            free(arr);
            return;
        }
        aux = aux->next;
        count++;
    }
    arr[count] = NULL; // Terminador NULL

    real_exec(path, arr, environ);

    count = 0;
    while (arr[count])
    {
        free(arr[count]);
        count++;
    }
    free(arr);
}

int exec_main(t_myshell *tshell)
{
    t_token *buff;
    char *path;
    char *path_aux;

    buff = tshell->tokens;
    while (buff->next)
    {
        path = get_path(tshell);
        if (path == NULL)
        {
            fprintf(stderr, "Error: no se pudo obtener el path\n");
            return ERROR_GENERIC;
        }

        path_aux = get_cmd_path(path, buff->content);
        if (path_aux == NULL)
        {
            free(path);
            fprintf(stderr, "Error: path_aux es nulo\n");
            return ERROR_GENERIC;
        }

        ft_exec(path_aux, tshell->environ, buff);

        buff = buff->next;

        free(path);
        free(path_aux);
    }
    return (SUCCESS);
}
