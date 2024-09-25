/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:34 by ecortes-          #+#    #+#             */
/*   Updated: 2024/09/24 22:02:55 by ecortes-         ###   ########.fr       */
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

void ctrld(int sig)
{
	(void)sig;
	exit(0);
}

void ctrl_(int sig)
{
	(void)sig;
}

void main_signals()
{
	signal(SIGINT, &ctrlc);
	signal(EOF, &ctrld);
	signal(SIGQUIT, &ctrl_);
}