/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 23:17:59 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/17 11:08:27 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	free_minishell(t_myshell *tshell, char *str)
{
	ft_free(str);
	ft_free(tshell->prompt);
	free_tokens(&tshell->tokens);
	free_comands(&tshell->comands);
}

static void reloop(char *str, char *pr, t_myshell *tm)
{
	perror(str);
	free_minishell(tm, pr);
	loop(tm);
}

void	loop(t_myshell *tshell)
{
	char *pr;

	pr = NULL;
	while (true)
	{
		pr = readline("MINISHELL$ ");
		if (!pr)
			exit(1);
		tshell->prompt = ft_strtrim(pr, " \n\t\r\v\f");
		if (count_quotes(tshell->prompt) == FALSE)
			reloop(BAD_QUOTES, pr, tshell);
		add_history(tshell->prompt);
		tokens(tshell->prompt, tshell);
		expander(tshell);
		comands(tshell);
		print_args(tshell);
		exec(tshell);
		free_minishell(tshell, pr);
	}
}
