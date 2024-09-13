CC=cc
CFLAGS=-Wall -Wextra -Werror
INCDIR=-Iinclude 
LIBS=-lreadline

SRCS =$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

NAME=myshell

all:$(NAME)

$(NAME):$(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)


%.o:%.c
	$(CC) $(CFLAGS) $(INCDIR) -g -c $< -o $@

clean:
	rm -rf $(OBJS)
fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re

