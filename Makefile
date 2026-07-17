NAME := bin/codexion
# ./bin/codexion 5 1000 250 250 250 10 100 fifo

CC := cc
CFLAGS := -I./include -Wall -Wextra -Werror -pthread

SRC := \
	src/coder.c \
	src/context.c \
	src/debug.c \
	src/get.c \
	src/main.c \
	src/pqueue.c \
	src/setup.c \
	src/sort.c \
	src/timestamp.c \
	src/traceback.c
OBJ := $(SRC:src/%.c=obj/%.o)


# Commands
# -----------------------------------------------------------------------------

all: $(NAME)

clean:
	rm -rf obj

fclean: clean
	rm -rf bin

re: fclean all


# Test commands
# -----------------------------------------------------------------------------

run: $(NAME)
	./$(NAME) 5 1000 250 250 250 10 100 fifo

test: norm valgrind helgrind drd

norm:
	@echo "\033[1;96m\nNORMINETTE"
	@echo "--------------------------------------------------------------------------------\033[0m"
	@norminette -RCheckForbiddenSourceHeader include src

valgrind: $(NAME)
	@echo "\033[1;96m\nVALGRIND"
	@echo "--------------------------------------------------------------------------------\033[0m"
	@valgrind --leak-check=full ./$(NAME)

helgrind: $(NAME)
	@echo "\033[1;96m\nHELGRIND"
	@echo "--------------------------------------------------------------------------------\033[0m"
	@valgrind --tool=helgrind ./$(NAME)

drd: $(NAME)
	@echo "\033[1;96m\nDRD"
	@echo "--------------------------------------------------------------------------------\033[0m"
	@valgrind --tool=drd ./$(NAME)


# Phonies
# -----------------------------------------------------------------------------

.PHONY: all clean fclean re test norm valgrind helgrind drd


# Files
# -----------------------------------------------------------------------------

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

$(NAME): $(OBJ) | bin
	$(CC) $(CFLAGS) $(OBJ) -o $@

bin:
	mkdir -p bin
