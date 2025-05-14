CC = cc
NAME = minishell
FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
       builtins/ft_echo.c \
       builtins/ft_env.c \
       builtins/ft_export.c \
       builtins/ft_pwd.c \
       builtins/ft_unset.c \
       builtins/ft_cd.c \
       builtins/ft_exit.c \
       builtins/builtins.c \

OBJ = $(SRCS:.c=.o)

INCLUDES = -I../../includes

READLINE_FLAGS = -lreadline -L/usr/lib -I/usr/include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
