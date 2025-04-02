CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline -lncurses

all: minishell

minishell: ctrls.o
	$(CC) $(CFLAGS) -o minishell ctrls.o $(LIBS)

clean:
	rm -f minishell ctrl_.o

