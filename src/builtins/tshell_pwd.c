/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:42:00 by ecortes-          #+#    #+#             */
/*   Updated: 2024/09/24 21:43:24 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void tshell_pwd()
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
	else
        perror("pwd");
}
