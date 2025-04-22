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

OBJ=$(SRCS:.c=.o)

LIBFT_DIR = ./Libft
readline_DIR = ../libraries/readline

LIBFT = $(LIBFT_DIR)/libft.a
READLINE_FLAGS = -lreadline -L/usr/lib -I/usr/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all clean fclean re