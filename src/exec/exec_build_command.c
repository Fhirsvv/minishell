/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:56:03 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:06:30 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void parse_symbols_for_convenience(t_myshell *tshell)
{
	t_token *aux;

	aux = tshell->tokens;
	while(aux)
	{
		if(aux->symbol == D_QUOTE || aux->symbol == S_QUOTE)
			aux->symbol = WORD;
		aux = aux->next;
	}
}

void exec_build_comands(t_myshell *tshell)
{
	t_token *aux;

	parse_symbols_for_convenience(tshell);
	aux = tshell->tokens;
	while(aux)
	{
		while(aux->symbol == WORD)
			aux = aux->next;
		
	}
	
}
