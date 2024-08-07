NAME        := minishell
CC        := gcc
FLAGS    := -Wall -Wextra -Werror  -fsanitize=address -g3
LDFLAGS     := -lreadline

SRCS        :=      src/main.c \
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
                        src/lexer/tokens.c \
                        src/lexer/tokens_utils.c \
                        src/path/path.c \
                        src/exec/exec.c \
                        src/exec/exec_build_command.c \
                        src/expander/expander.c \
                        src/utils/utils_main.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


