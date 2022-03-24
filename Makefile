# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 16:07:19 by rchampli          #+#    #+#              #
#    Updated: 2022/03/24 02:31:45 by grosendo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

cc			= gcc

CFLAGS		= -Wall -Wextra -Werror 

INCFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

LINKFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib

SRCS		= ./srcs/builtins/cd.c ./srcs/builtins/echo.c ./srcs/builtins/env.c ./srcs/builtins/env2.c ./srcs/builtins/exit.c ./srcs/builtins/export.c ./srcs/builtins/export2.c ./srcs/builtins/is_a_builtin.c ./srcs/builtins/pwd.c ./srcs/builtins/unset.c ./srcs/entities/block.c ./srcs/entities/execline.c ./srcs/entities/shell.c ./srcs/entities/token.c ./srcs/execution/child.c ./srcs/execution/execute.c ./srcs/execution/execute_block.c ./srcs/execution/front_exec.c ./srcs/execution/loop.c ./srcs/main.c ./srcs/parsing/heredoc.c ./srcs/parsing/make_pipes.c ./srcs/parsing/parse.c ./srcs/parsing/parse_block.c ./srcs/parsing/parse_execline.c ./srcs/parsing/parse_token.c ./srcs/parsing/parse_token_two.c ./srcs/parsing/translate_env.c ./srcs/signal.c ./srcs/utils/ft_free_array.c ./srcs/utils/ft_free_split.c ./srcs/utils/ft_isalphanum.c ./srcs/utils/ft_isinset.c ./srcs/utils/ft_istrchr.c ./srcs/utils/ft_iswhitespace.c ./srcs/utils/ft_itoa_spe.c ./srcs/utils/ft_printerror.c ./srcs/utils/ft_printf_return.c ./srcs/utils/ft_split.c ./srcs/utils/ft_strchr.c ./srcs/utils/ft_strchr_i.c ./srcs/utils/ft_strcmp.c ./srcs/utils/ft_strdiff.c ./srcs/utils/ft_strdup.c ./srcs/utils/ft_strequ.c ./srcs/utils/ft_strjoin.c ./srcs/utils/ft_strlen.c ./srcs/utils/ft_strncmp.c ./srcs/utils/ft_strndup.c ./srcs/utils/ft_strstartwith.c ./srcs/utils/ft_substr.c ./srcs/utils/skip_whitespaces.c

all: $(NAME)

OBJS	= $(SRCS:.c=.o)

$(NAME)	: $(OBJS) srcs/minishell.h
	@$(CC) $(OBJS) -lreadline $(INCFLAGS) $(LINKFLAGS) -o $(NAME)
	@echo "DONE :\n\n" " __  __ ___ _  _ ___ ___ _  _ ___ _    _   \n|  \\/  |_ _| \\| |_ _/ __| || | __| |  | |   \n| |\\/| || || .. || |\\__ \\ __ | _|| |__| |__ \n|_|  |_|___|_|\\_|___|___/_||_|___|____|____|"
%.o:%.c
	@$(CC) $(CFLAGS) $(INCFLAGS) -c  $^ -o $@
	@echo "DONE : " $^
clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re all fclean clean