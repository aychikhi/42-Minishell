NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/ft_isalnum.c ./utils/ft_isalpha.c ./utils/ft_isdigit.c ./utils/ft_itoa.c ./utils/ft_lstnew.c\
		 ./utils/ft_lstadd_back.c checker_fun.c helper.c helper1.c helper2.c tokeniser.c main.c\

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