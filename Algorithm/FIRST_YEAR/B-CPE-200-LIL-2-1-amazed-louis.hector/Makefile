##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile amazed
##

SRC		=	src/main.c \
			src/display.c \
			src/algorithm.c \
			src/parsing/parsing.c \
			src/parsing/create_matrix.c \
			src/parsing/recover_room.c \
			src/parsing/recover_link.c

NAME = amazed

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude -Llib/my -lmy -Wall -Wextra -Werror

LCFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

libmy.a:
	$(MAKE) -C lib/my

clean:
	$(MAKE) -C lib/my clean
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	$(MAKE) -C lib/my fclean
	rm -f $(NAME)
	rm -f $(LCNAME)
	rm -f libmy.a

re:		fclean all

debug:
	$(MAKE) -C lib/my all
	gcc -g -o $(NAME) $(OBJ) $(CFLAGS)

tests_run: clean
	gcc -o unit_tests $(TESTSRC) \
		--coverage -lcriterion $(CFLAGS)

	./unit_tests

	gcovr --exclude inclue/
	gcovr --exclude inclue/ --branches
