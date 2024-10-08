/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:18:48 by ecortes-          #+#    #+#             */
/*   Updated: 2024/09/24 18:17:14 by ecortes-         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define SUCCESS 0
#define ERROR_GENERIC -1
#define ERROR_MEMORY -2
#define ERROR_INVALID_PARAMETER -3

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
void	free_arr(char **split_arr);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_semi_strtrim(char const *s1, char const *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
t_command	*ft_command_new(char **args, char *c_path);
void	ft_commandadd_back(t_command **lst, t_command *new);
void ft_tokenadd_after(t_token **lst, t_token *new, t_token *wh);
void ft_tokensubstitute(t_token **lst, t_token *new, t_token *wh);


//----TOKENS--------------------------------------------------------------
void tokens_and_quotes(char *prompt, t_myshell *tshell);
void add_token_and_free(char *start_q, char *end_q, char *prompt, t_myshell *tshell);
int token_type(char *str);
int	count_quotes(const char *prompt);
void update_last_token_symbol(t_myshell *tshell, int new_symbol);
void split_various_dolar(t_myshell *tshell);


//----MAIN FUNCTIONS------------------------------------------------------
void loop(t_myshell *tshell);


//----PATH FUNCTIONS-------------------------------------------------------
char *get_cmd_path(char *path, char *cmd);
char *get_path(t_myshell *tshell);
void ft_free2(char *arr1, char *arr2);


//----EXEC FUNCTIONS------------------------------------------------------
int build_comands_main(t_myshell *tshell);
char **add_to_matrix(char **arr, char *new);
int args_size(t_token *token);
int new_command_symbols(t_myshell *tshell, t_token *aux);
t_token *new_command(t_myshell *tshell, t_token *aux);

void main_exec(t_myshell *tshell);


//----EXPANDER FUNCTIONS--------------------------------------------------
int expander_main(t_myshell *tshell);
char *replace_substr(char *prompt, char *old_str, char *new_str);
char *substr_part_expand(char *auxstr);


//----UTILS FUNCTIONS------------------------------------------------------
int init_tshell(t_myshell *myshell, char **environ);
void free_myshell(t_myshell *tshell);
const char *get_token_type_name(int symbol);
void print_tokens(t_myshell *tshell);
void free_loop(t_myshell *tshell);
int how_many_finds(char *str, int c);
void print_args(t_myshell *tshell);

//----SIGNALS-----------------------------------------------------------------
void main_signals();

#endif