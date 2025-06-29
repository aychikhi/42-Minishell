CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I includes/ -I/goinfre/$(USER)/homebrew/opt/readline/include -g -fsanitize=address
LDFLAGS = -lreadline -lncurses -L/goinfre/$(USER)/homebrew/opt/readline/lib

SRCS = src/main.c \
       src/parsing/utils/ft_strcpy.c src/parsing/utils/ft_strncpy.c src/parsing/utils/ft_substr.c \
       src/parsing/utils/ft_lstadd_back.c src/parsing/utils/add_new.c src/parsing/utils/add_newfile.c \
       src/parsing/init/init_fun.c src/parsing/init/init_fun1.c \
       src/parsing/token/helper.c src/parsing/token/helper1.c src/parsing/token/helper2.c \
       src/parsing/token/helper3.c src/parsing/token/helper4.c src/parsing/token/helper5.c \
       src/parsing/token/helper6.c src/parsing/token/tokeniser.c src/parsing/token/wildcard_helper.c \
       src/parsing/token/helpeer.c src/parsing/token/helper7.c src/parsing/token/helper8.c\
       src/parsing/token/parser/parser.c src/parsing/token/parser/parser1.c\
       src/parsing/token/parser/parser2.c src/parsing/token/parser/parser3.c\
       src/parsing/utils/ft_strlen.c src/parsing/utils/ft_strdup.c src/parsing/utils/ft_isalnum.c \
       src/parsing/utils/ft_isalpha.c src/parsing/utils/ft_isdigit.c src/parsing/utils/ft_lstnew.c \
       src/parsing/utils/ft_strcmp.c src/parsing/utils/ft_strjoin.c src/parsing/utils/add_backfile.c \
       src/parsing/utils/ft_strchr.c src/parsing/utils/ft_putstr_fd.c src/parsing/utils/ft_strncmp.c \
       src/parsing/utils/ft_atoi.c src/parsing/utils/ft_split.c src/parsing/utils/ft_itoa.c \
       src/parsing/utils/ft_file_exists.c src/parsing/utils/print_ballas.c\
       src/execution/builtins/ft_echo.c src/execution/builtins/ft_env.c \
       src/execution/builtins/ft_export.c src/execution/builtins/ft_pwd.c \
       src/execution/builtins/ft_unset.c src/execution/builtins/ft_cd.c \
       src/execution/builtins/ft_exit.c src/execution/builtins/builtins.c \
       src/execution/ft_wildcard.c src/execution/external.c \
       src/execution/bibex.c src/execution/help.c src/execution/heredoc.c src/execution/externals_help1.c src/execution/heredoc_help.c\
       src/execution/signals.c src/execution/signals_help.c src/execution/bibex_help.c\
       src/execution/external_helper.c src/parsing/token/help_main.c

OBJS = $(SRCS:.c=.o)

READLINE_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re