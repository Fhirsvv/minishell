/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:18:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/23 15:40:13 by ecortes-         ###   ########.fr       */
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

//----TOKENS--------------------------------------------------------------
void new_tokkenice(char *prompt, t_myshell *tshell);
void tokens_and_quotes(char *prompt, t_myshell *tshell);
int token_type(char *str);

//----MAIN FUNCTIONS------------------------------------------------------
void loop(t_myshell *tshell);
void init_tshell(t_myshell *myshell, char **environ);
void free_myshell(t_myshell *tshell);

#endif