NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror 

SRCS = ./utils/ft_split.c ./utils/ft_lstadd_back.c ./utils/ft_lstnew.c ./utils/ft_isspecial.c ./utils/ft_strlen.c main.c \

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