##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile corewar
##

SRC		=	main.c 								\
			src/parsing/flags.c 				\
			src/champions/create_champions.c 	\
			src/virtual_machine/init_arena.c    \
			src/processes/create_processes.c    \
			src/free_functions/free.c 	 		\
			src/instructions_code/add.c 		\
			src/instructions_code/aff.c 		\
			src/instructions_code/fork.c 		\
			src/instructions_code/ld.c 			\
			src/instructions_code/ldi.c 		\
			src/instructions_code/lfork.c 		\
			src/instructions_code/live.c 		\
			src/instructions_code/lld.c 		\
			src/instructions_code/lldi.c 		\
			src/instructions_code/or.c 			\
			src/instructions_code/st.c 			\
			src/instructions_code/sti.c 		\
			src/instructions_code/subb.c 		\
			src/instructions_code/xor.c 		\
			src/instructions_code/zjmp.c 		\
			src/instructions_code/and.c 		\
			src/instructions_code/check_types.c \
			src/instructions_code/modif_proces.c\
			src/virtual_machine/check_winner.c  \

NAME = corewar

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude -Llib/my -lmy -Wall -Wextra -Werror -g

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
