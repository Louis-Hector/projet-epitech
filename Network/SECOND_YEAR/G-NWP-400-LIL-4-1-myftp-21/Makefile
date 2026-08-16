##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

SRC		=	src/main.c \
			src/poll.c \
			src/clients_actions.c \
			src/file_commands.c \
			src/informational_command.c \
			src/miscellaneous_command.c \
			src/login_commands.c \
			src/logout_command.c \
			src/transfer_commands.c \
			src/path_command.c

NAME = myftp

OBJ = $(SRC:.c=.o)

CC = epiclang

LCNAME = unit_tests

CFLAGS = -std=gnu17 -Wall -Wextra -Werror -g -I include/

LCFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:		fclean all

tests_run: clean
	gcc -o unit_tests $(TESTSRC) \
		--coverage -lcriterion $(CFLAGS)

	./unit_tests

	gcovr --exclude inclue/
	gcovr --exclude inclue/ --branches
