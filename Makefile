NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC =	main.c signals.c signals_handler.c term.c \
		lexer/lexer_core.c lexer/lexer_word.c lexer/lexer_ops.c lexer/lexer_string.c lexer/lexer_token.c lexer/lexer_word_utils.c \
		parser/parser_core.c parser/parser_arrays.c parser/parser_utils.c parser/parser_redir.c parser/parser_cmd.c parser/parser_word.c parser/parser_pipeline.c parser/parser_cleanup.c parser/parser_redir_utils.c parser/parser_word_utils.c \
		exec/exec_pipeline.c exec/exec_utils.c exec/exec_builtin.c exec/exec_redirection.c exec/exec_array_utils.c exec/exec_child.c exec/exec_heredoc.c exec/exec_wait.c \
		builtins/builtin_utils.c builtins/builtin_echo.c builtins/builtin_pwd.c \
		builtins/builtin_cd.c builtins/builtin_cd_utils.c \
		builtins/builtin_exit.c builtins/builtin_env.c builtins/builtin_export.c builtins/builtin_unset.c \
		builtins/builtin_dispatch.c utils/path_utils.c utils/path_checker.c utils/path_resolver.c \
		env/env_utils.c env/env_access.c env/env_modify.c env/env_lifecycle.c \
		expand/expand_word.c expand/expand_variable.c expand/expand_utils.c expand/expand_char.c
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include -I $(LIBFT_DIR)/include
LIBS = -L $(LIBFT_DIR) -lft -lreadline

YELLOW = \033[0;33m
RESET = \033[0m
PREFIX = $(YELLOW)[$(NAME)]$(RESET)

all: $(LIBFT) $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_FILES) $(LIBS) -o $(BIN_DIR)/$(NAME)
	@echo "$(PREFIX) Link complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(PREFIX) Compiling: $<"

$(LIBFT):
	@echo "$(PREFIX) Building libft:"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(PREFIX) Cleaned objects"

fclean: clean
	@rm -rf $(BIN_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(PREFIX) Removed executables"

re: fclean all

.PHONY: all clean fclean re
