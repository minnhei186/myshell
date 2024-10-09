# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 13:58:08 by hosokawa          #+#    #+#              #
#    Updated: 2024/10/09 13:43:25 by hosokawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror
#INCDIR=-Iinclude 
INCDIR=-Iinclude -I/opt/homebrew/opt/readline/include  
LIBDIR=libft
#LIBS=-lreadline
LIBS=-L/opt/homebrew/opt/readline/lib -lreadline -L$(LIBDIR) -lft


SRCS =$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

LIB_NAME=libft.a
NAME=myshell


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

