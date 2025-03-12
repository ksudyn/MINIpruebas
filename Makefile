NAME = minishell

CC = cc
HEADERS = -I ./includes
CFLAGS = -Wall -Wextra -Werror $(HEADERS)

SRCS := $(addprefix src/, \
	cd.c  echo.c  env.c  exit.c  export.c  pwd.c  unset.c)

SRCS_LIB := $(addprefix ./libft/, \
	ft_putchar.c	ft_isdigit.c ft_putchar_fd.c	ft_substr.c ft_hexadec.c	ft_putnbr.c\
	ft_putptr.c	ft_putstr.c	ft_putnbru.c	ft_putstr_fd.c ft_split.c	ft_strlen.c ft_memcpy.c\
	ft_atoi.c	ft_atol.c	ft_lstadd_back_bonus.c	ft_lstadd_front_bonus.c	ft_lstclear_bonus.c\
	ft_lstlast_bonus.c	ft_lstnew_bonus.c	ft_lstsize_bonus.c	ft_sqrt.c ft_calloc.c ft_is_sing.c)

OBJS = $(SRCS:.c=.o) $(SRCS_LIB:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
