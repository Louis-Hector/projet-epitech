##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## gcc my_printf
##

NAME	=	my_hunter

OBJ		=	$(SRC:.c=.o)

all: 	$(NAME)

CFLAGS += -lcsfml-system -lcsfml-window libmy.a -I include

$(NAME): $(OBJ)
		$(MAKE) -C lib/my/
		cp lib/my/libmy.a .
		gcc -o $(NAME) myhunter.c -lcsfml-graphics -lcsfml-audio $(CFLAGS)

clean:
		rm -f $(OBJ)
		rm libmy.a
		rm lib/my/libmy.a

fclean:
		rm -f $(NAME)
		rm libmy.a
		rm lib/my/*.o
		rm lib/my/libmy.a

re:		fclean all
