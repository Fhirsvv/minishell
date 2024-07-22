/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:18:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/07/22 18:34:49 by ecortes-         ###   ########.fr       */
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

// ----LIBFT/MODIFICATED  LIBFT FUNCTIONS----------------------------------
void	*ft_calloc(size_t num, size_t size);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_token_new(char *str, int type);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);

#endif