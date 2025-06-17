CC = cc
NAME = minishell
# CFLAGS = -Wall -Wextra -Werror #-g #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I includes/ -I/goinfre/$(USER)/homebrew/opt/readline/include
LDFLAGS = -L/goinfre/$(USER)/homebrew/opt/readline/lib -lreadline

SRCS = src/execution/main.c \
       src/utils/ft_strcpy.c src/utils/ft_strncpy.c src/utils/ft_substr.c \
       src/utils/ft_lstadd_back.c src/utils/add_new.c src/utils/add_newfile.c \
       src/init/init_fun.c src/init/init_fun1.c \
       src/token/helper.c src/token/helper1.c src/token/helper2.c \
       src/token/helper3.c src/token/helper4.c src/token/helper5.c \
       src/token/helper6.c src/token/tokeniser.c src/token/wildcard_helper.c \
       src/token/helpeer.c \
       src/parser/parser.c src/parser/parser1.c \
       src/utils/ft_strlen.c src/utils/ft_strdup.c src/utils/ft_isalnum.c \
       src/utils/ft_isalpha.c src/utils/ft_isdigit.c src/utils/ft_lstnew.c \
       src/utils/ft_strcmp.c src/utils/ft_strjoin.c src/utils/add_backfile.c \
       src/utils/ft_strchr.c src/utils/ft_putstr_fd.c src/utils/ft_strncmp.c \
       src/utils/ft_atoi.c src/utils/ft_split.c src/utils/ft_itoa.c \
       src/utils/ft_file_exists.c \
       src/execution/builtins/ft_echo.c src/execution/builtins/ft_env.c \
       src/execution/builtins/ft_export.c src/execution/builtins/ft_pwd.c \
       src/execution/builtins/ft_unset.c src/execution/builtins/ft_cd.c \
       src/execution/builtins/ft_exit.c src/execution/builtins/builtins.c \
       src/execution/ft_wildcard.c src/execution/external.c \
       src/execution/bibex.c src/execution/help.c src/execution/heredoc.c src/execution/externals_help1.c src/execution/heredoc_help.c\
       src/execution/signals.c src/execution/signals_help.c src/execution/bibex_help.c\
       src/execution/external_helper.c

OBJS = $(SRCS:.c=.o)

# INCLUDES = -Iincludes

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