NAME = minishell

CC = cc
HEADERS = -I ./includes
CFLAGS = -Wall -Wextra -Werror $(HEADERS)

SRCS := \
	src/main/main.c \
	src/builtins/cd.c \
	src/builtins/cpy_envp.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/execute_builtins.c\
	src/builtins/execute_command.c\
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/builtins/utils.c \
	src/builtins/utils_export.c\
	src/ctrls/ctrls.c \
	src/redirects/redirects.c

SRCS_LIB := $(addprefix ./libft/, \
	ft_putchar.c	ft_isdigit.c ft_putchar_fd.c	ft_substr.c ft_hexadec.c	ft_putnbr.c\
	ft_putptr.c	ft_putstr.c	ft_putnbru.c	ft_putstr_fd.c ft_split.c	ft_strlen.c ft_memcpy.c\
	ft_atoi.c	ft_atol.c	ft_lstadd_front_bonus.c	ft_lstclear_bonus.c\
	ft_lstsize_bonus.c	ft_sqrt.c ft_calloc.c ft_is_sing.c ft_strjoin.c\
	ft_isalpha.c ft_isalnum.c ft_strcmp.c ft_strdup.c ft_strncmp.c ft_strchr.c\
	ft_strndup.c ft_strtrim.c)

OBJS = $(SRCS:.c=.o) $(SRCS_LIB:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
