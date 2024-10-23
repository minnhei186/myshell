
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCDIR=include
SRCS=src/ft_atoi.c \
	src/ft_memset.c \
	src/ft_strlcat.c \
	src/ft_bzero.c \
	src/ft_p_output.c \
	src/ft_strlcpy.c \
	src/ft_c_output.c \
	src/ft_percent_output.c \
	src/ft_strlen.c \
	src/ft_calloc.c \
	src/ft_printf.c \
	src/ft_strmapi.c \
	src/ft_d_output.c \
	src/ft_printf_numComvert.c \
	src/ft_strncmp.c \
	src/ft_i_output.c \
	src/ft_printf_util.c \
	src/ft_strnstr.c \
	src/ft_isalnum.c \
	src/ft_putchar_fd.c \
	src/ft_strrchr.c \
	src/ft_isalpha.c \
	src/ft_putendl_fd.c \
	src/ft_strtrim.c \
	src/ft_isascii.c \
	src/ft_putnbr_fd.c \
	src/ft_substr.c \
	src/ft_isdigit.c \
	src/ft_putstr_fd.c \
	src/ft_tolower.c \
	src/ft_isprint.c \
	src/ft_s_output.c \
	src/ft_toupper.c \
	src/ft_itoa.c \
	src/ft_split.c \
	src/ft_u_output.c \
	src/ft_memchr.c \
	src/ft_strchr.c \
	src/ft_x_output.c \
	src/ft_memcmp.c \
	src/ft_strdup.c \
	src/ft_xx_output.c \
	src/ft_memcpy.c \
	src/ft_striteri.c \
	src/get_next_line.c \
	src/ft_memmove.c \
	src/ft_strjoin.c \
	src/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
Library= ar rc
NAME = libft.a

all : $(NAME)

$(NAME):$(OBJS)
	$(Library) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY: all clean fclean re
