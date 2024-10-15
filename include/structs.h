/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:55 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/15 18:36:00 by ecortes-         ###   ########.fr       */
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

enum e_builtins
{
	CD = 0,
	LS,
	ECHO,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NO_BUILTIN
};

typedef struct s_fds
{
	char	*input_file;
	char	*output_file;
	char	*apend_file;

	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_fds;

typedef struct s_command
{
	char **args;
	char *comand_path;
	t_fds	*fds;
	struct s_command *next;
}	t_comand;

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
	int pipes_count;
	t_token *tokens;
	t_comand *comands;
}	t_myshell;

#endif