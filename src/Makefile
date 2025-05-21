CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = execution/main.c \
       utils/ft_strcpy.c utils/ft_strncpy.c utils/ft_substr.c \
       utils/ft_lstadd_back.c utils/add_new.c utils/add_newfile.c \
       init/init_fun.c init/init_fun1.c \
       token/helper.c token/helper1.c token/helper2.c \
       token/helper3.c token/helper4.c token/helper5.c \
       token/helper6.c token/tokeniser.c \
       parser/parser.c parser/parser1.c \
       utils/ft_strlen.c utils/ft_strdup.c utils/ft_isalnum.c \
       utils/ft_isalpha.c utils/ft_isdigit.c utils/ft_lstnew.c \
       utils/ft_strcmp.c utils/ft_strjoin.c utils/add_backfile.c \
       utils/ft_strchr.c utils/ft_putstr_fd.c utils/ft_strncmp.c \
       utils/ft_atoi.c utils/ft_split.c \
       execution/builtins/ft_echo.c execution/builtins/ft_env.c \
       execution/builtins/ft_export.c execution/builtins/ft_pwd.c \
       execution/builtins/ft_unset.c execution/builtins/ft_cd.c \
       execution/builtins/ft_exit.c execution/builtins/builtins.c \
       execution/external.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -Iincludes

READLINE_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(READLINE_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re