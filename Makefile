NAME = codexion

DIR_LIBFT = libft/
LIBFT = $(DIR_LIBFT)libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft

SRC = main.c
OBJ = $(SRC:.c=.o)

# Commands
# -----------------------------------------------------------------------------

all: $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	rm -f $(NAME) $(ARGGEN)
	$(MAKE) fclean -C $(DIR_LIBFT)

re: fclean all

# Test commands
# -----------------------------------------------------------------------------

test: norm valgrind

norm:
	@echo ""
	norminette -RCheckForbiddenSourceHeader $(SRC) $(NAME).h

valgrind: all
	@echo ""
	valgrind --leak-check=full ./$(NAME)

# Phonies
# -----------------------------------------------------------------------------

.PHONY: all clean fclean re test norm valgrind

# Files
# -----------------------------------------------------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)
