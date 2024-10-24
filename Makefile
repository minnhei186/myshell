# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 13:58:08 by hosokawa          #+#    #+#              #
#    Updated: 2024/10/23 18:40:11 by hosokawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
# CFLAGS+=-fsanitize=address,undefined
#INCDIR=-Iinclude
INCDIR=-Iinclude -I/opt/homebrew/opt/readline/include
LIBDIR=libft
#LIBS=-lreadline
LIBS=-L/opt/homebrew/opt/readline/lib -lreadline -L$(LIBDIR) -lft


SRCS=src/builtin.c \
	src/parser.c \
	src/builtin_cd.c \
	src/parser_append.c \
	src/builtin_cd_utils.c \
	src/parser_append_redirect.c \
	src/builtin_echo.c \
	src/parser_append_utils.c \
	src/builtin_env.c \
	src/path_finder.c \
	src/builtin_exit.c \
	src/pipe.c \
	src/builtin_export.c \
	src/readline.c \
	src/builtin_pwd.c \
	src/redirect_prepare.c \
	src/builtin_unset.c \
	src/redirect_prepare_element.c \
	src/builtin_utils.c \
	src/redirect_prepare_heredoc.c \
	src/error.c \
	src/redirect_prepare_heredoc_utils.c \
	src/error_token_parse.c \
	src/redirect_set_reset.c \
	src/exec.c \
	src/ft_strutils.c \
	src/shell_map.c \
	src/exec_mlt_process.c \
	src/shell_map_set_unset.c \
	src/exec_mlt_process_utils.c \
	src/shell_map_utils.c \
	src/expand.c \
	src/shell_refunc_atol.c \
	src/expand_expander.c \
	src/shell_refunc_first.c \
	src/expand_expander_element.c \
	src/shell_refunc_second.c \
	src/expand_expander_element_utils.c \
	src/signal.c \
	src/expand_expander_utils.c \
	src/signal_handler.c \
	src/expand_memory_utils.c \
	src/tokenizer.c \
	src/expand_remover.c \
	src/tokenizer_make_token.c \
	src/free.c \
	src/tokenizer_make_token_utils.c \
	src/free_operation.c \
	src/tokenizer_utils.c \
	src/info_data.c \
	src/close_safely.c

OBJS=$(SRCS:.c=.o)

LIB_NAME=libft.a
NAME=minishell


all:$(LIB_NAME) $(NAME)

$(NAME):$(OBJS)
	$(CC)  $(CFLAGS) -L$(LIBDIR) -lft $(OBJS) -o $(NAME) $(LIBS)


%.o:%.c
	$(CC) $(CFLAGS) $(INCDIR) -g -c $< -o $@

$(LIB_NAME):
	$(MAKE) -C $(LIBDIR)

clean:
	$(MAKE) clean -C $(LIBDIR)
	rm -rf $(OBJS)
fclean:clean
	$(MAKE) fclean -C $(LIBDIR)
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re

