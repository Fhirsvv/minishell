# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 00:01:24 by ecortes-          #+#    #+#              #
#    Updated: 2024/10/12 00:25:19 by ecortes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

SRCS = src/main.c \
        src/no_libft/ft_substr.c \
        src/no_libft/ft_strlen.c \
        src/no_libft/ft_tokenadd_back.c \
        src/no_libft/ft_strdup.c \
        src/no_libft/ft_split.c \
        src/no_libft/ft_calloc.c \
        src/no_libft/ft_token_new.c \
        src/no_libft/ft_strchr.c \
        src/no_libft/ft_array_duplicate.c \
        src/no_libft/ft_strtrim.c \
        src/no_libft/ft_strncmp.c \
        src/no_libft/ft_strjoin.c \
        src/no_libft/ft_command_new.c \
        src/no_libft/ft_commandadd_back.c \
        src/no_libft/ft_tokenadd_after.c \
        src/no_libft/ft_tokensubstitute.c \
        src/path/path.c \
        src/exec/exec.c \
        src/comands/comands.c \
        src/comands/commands_utils.c \
        src/comands/setup_comands.c \
        src/expander/expander.c \
        src/utils/utils.c \
        src/utils/utils2.c \
        src/signals/signals.c \
        src/builtins/tshell_cd.c \
        src/builtins/tshell_pwd.c \
        src/tokens/tokens.c \
        src/tokens/utils.c \
        src/tokens/utils2.c \
        src/loop/loop.c
                          
OBJS = $(SRCS:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) compilado con éxito"

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Objetos eliminados"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) eliminado"

re: fclean all

.PHONY: all clean fclean re