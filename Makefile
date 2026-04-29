NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c
OBJ = $(SRC:.c=.o)

# Commands
# -----------------------------------------------------------------------------

all: $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

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

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
