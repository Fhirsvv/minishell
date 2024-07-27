/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:18:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/24 15:38:54 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "structs.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

//----LIBFT/MODIFICATED  LIBFT FUNCTIONS----------------------------------
void	*ft_calloc(size_t num, size_t size);
t_token	*ft_token_new(char *str, int type);
void	ft_tokenadd_back(t_token **lst, t_token *new);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	**ft_array_duplicate(char **arr);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

//----TOKENS--------------------------------------------------------------
void new_tokkenice(char *prompt, t_myshell *tshell);
void tokens_and_quotes(char *prompt, t_myshell *tshell);
int token_type(char *str);

//----MAIN FUNCTIONS------------------------------------------------------
void loop(t_myshell *tshell);
void init_tshell(t_myshell *myshell, char **environ);
void free_myshell(t_myshell *tshell);

//----PATH FUNCTIONS-------------------------------------------------------
char *get_cmd_path(char *path, char *cmd);
char *get_path(t_myshell *tshell);


//----EXEC FUNCTIONS------------------------------------------------------
void exec_things(t_myshell *tshell);
#endif