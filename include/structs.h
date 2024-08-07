/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:55 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/07 17:06:04 by ecortes-         ###   ########.fr       */
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
	WORD,
	D_QUOTE,
	S_QUOTE
};

typedef struct s_command
{
	char **args;
	char *comand_path;
	struct s_command *next;
}	t_command;

typedef struct s_token
{
	char *content;
	int symbol;
	struct s_token *next;
}	t_token;

typedef struct s_myshell
{
	char **environ;
	char *path;
	char *prompt;
	t_token *tokens;
	t_command *comands;
}	t_myshell;

#endif