NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c validate.c context.c error.c
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

run: $(NAME)
	./$(NAME) 5 1000 250 250 250 10 100 fifo

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
