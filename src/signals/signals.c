/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:34 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/11 23:10:32 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void ctrlc(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void signals()
{
	signal(SIGINT, &ctrlc);
}