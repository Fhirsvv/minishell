/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:16:38 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/11 23:38:26 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_after(t_myshell *tshell, char **arr, t_token *new, int *i)
{
	while (arr[*i])
	{
		ft_tokenadd_after(&tshell->tokens,
			ft_token_new(ft_strjoin("$", arr[*i]), WORD), new);
		new = new->next;
		*i = *i + 1;
	}
}
