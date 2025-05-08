NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = main.c ./utils/ft_strcpy.c ./utils/ft_strncpy.c ./utils/ft_substr.c ./utils/ft_lstadd_back.c ./utils/add_new.c ./utils/add_newfile.c ./init/init_fun.c ./init/init_fun1.c\
		./token/helper.c ./token/helper1.c ./token/helper2.c ./token/helper3.c ./token/helper4.c ./token/helper5.c ./token/helper6.c ./token/tokeniser.c ./parser/parser.c ./parser/parser1.c\
 		./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/ft_isalnum.c ./utils/ft_isalpha.c ./utils/ft_isdigit.c ./utils/ft_lstnew.c ./utils/ft_strcmp.c ./utils/ft_strjoin.c ./utils/add_backfile.c\

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