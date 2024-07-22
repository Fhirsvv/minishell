/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:55 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 18:21:03 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

enum e_token_types
{
	PIPE,
	REDIR_D,
	DOBLE_REDIR_D,
	REDIR_I,
	HERE_DOC,
	WORD
};

typedef struct s_token
{
	char *content;
	int symbol;
	struct s_token *next;
}	t_token;

typedef struct s_myshell
{
	char **environ;
	char *prompt;
	t_token *tokens;
}	t_myshell;

#endif