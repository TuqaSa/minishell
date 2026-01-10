LIB_NAME = libft
NAME = $(LIB_NAME).a

SRC_DIR = src
OBJ_DIR = obj
LIBFT_SRC_DIR = $(SRC_DIR)/libft
PRINTF_SRC_DIR = $(SRC_DIR)/ft_printf
GNL_SRC_DIR = $(SRC_DIR)/gnl

LIBFT_SRC = ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_atol.c ft_isalpha.c \
	ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
	ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
	ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
	ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c \
	ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_striteri.c ft_strtrim.c

PRINTF_SRC = ft_print.c ft_printf.c ft_decimal.c

GNL_SRC = get_next_line.c get_next_line_utils.c

LIBFT_OBJ = $(addprefix $(OBJ_DIR)/libft/, $(LIBFT_SRC:.c=.o))
PRINTF_OBJ = $(addprefix $(OBJ_DIR)/ft_printf/, $(PRINTF_SRC:.c=.o))
GNL_OBJ = $(addprefix $(OBJ_DIR)/gnl/, $(GNL_SRC:.c=.o))
OBJS = $(LIBFT_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

CFLAGS = -Wall -Wextra -Werror -Iinclude
INCLUDE = -I include

YELLOW = \033[0;33m
RESET = \033[0m
LIBFT_PREFIX = $(YELLOW)[$(LIB_NAME)]$(RESET)
PRINTF_PREFIX = $(YELLOW)[ft_printf]$(RESET)
GNL_PREFIX = $(YELLOW)[gnl]$(RESET)

all: $(NAME)

$(OBJ_DIR)/libft/%.o: $(LIBFT_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/libft
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(LIBFT_PREFIX) Compiling: $<"

$(OBJ_DIR)/ft_printf/%.o: $(PRINTF_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/ft_printf
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(PRINTF_PREFIX) Compiling: $<"

$(OBJ_DIR)/gnl/%.o: $(GNL_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/gnl
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(GNL_PREFIX) Compiling: $<"

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(LIBFT_PREFIX) Link complete: $(NAME)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(LIBFT_PREFIX) Cleaning objects"

fclean: clean
	@rm -f $(NAME)
	@echo "$(LIBFT_PREFIX) Cleaning executable"

re: fclean all

.PHONY: all clean fclean re
