NAME := bin/codexion

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread

DIR_SRC := src
DIR_OBJ := obj
SRC := \
	src/context.c \
	src/error.c \
	src/get.c \
	src/main.c \
	src/time.c
OBJ := $(SRC:src/%.c=obj/%.o)


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
	norminette -RCheckForbiddenSourceHeader src include

valgrind: all
	@echo ""
	valgrind --leak-check=full ./$(NAME)


# Phonies
# -----------------------------------------------------------------------------

.PHONY: all clean fclean re test norm valgrind


# Files
# -----------------------------------------------------------------------------

obj/%.o: src/%.c obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir obj

$(NAME): $(OBJ) bin
	$(CC) $(CFLAGS) $(OBJ) -o $@

bin:
	mkdir bin
