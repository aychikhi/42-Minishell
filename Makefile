NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror 

SRCS = ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/ft_isalnum.c ./utils/ft_isalpha.c ./utils/ft_isdigit.c ./utils/ft_itoa.c\
		 checker_fun.c helper.c tokeniser.c main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) minishell.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean