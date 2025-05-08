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

LIBFT_DIR = ./Libft
READLINE_DIR = ../libraries/readline

LIBFT = $(LIBFT_DIR)/libft.a

#LINUX FLAGS 
READLINE_FLAGS = -lreadline -L/usr/lib -I/usr/include

CYAN = \033[1;36m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m


TOTAL_SRCS = $(words $(SRCS))

all: $(NAME)
	@echo "$(GREEN)🎉 Build complete! $(NAME) is ready to shine! ✨$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Libft built successfully!$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)🔨 Linking $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)
	@echo "$(GREEN)🚀 $(NAME) created! Ready to launch!$(RESET)"


COUNT = 0
%.o: %.c
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	@printf "\r$(YELLOW)🔍 Compiling sources... [$(COUNT)/$(TOTAL_SRCS)]$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@if [ $(COUNT) -eq $(TOTAL_SRCS) ]; then \
		echo "\n$(GREEN)✅ Compilation complete!$(RESET)"; \
	fi

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all
	@echo "$(CYAN)🔄 Rebuild complete! Fresh start!$(RESET)"

.PHONY: all clean fclean re

love:
	@echo "$(GREEN)💖 Made with love for minishell enthusiasts! 💖$(RESET)"

ballas:
	@echo "$(BLUE)💎 Ballas! GANG  💎$(RESET)"
