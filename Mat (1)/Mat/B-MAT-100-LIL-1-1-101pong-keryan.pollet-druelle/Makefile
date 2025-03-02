##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## gcc my_printf
##

NAME	=	101pong

OBJ		=	$(SRC:.c=.o)

all: 	$(NAME)


$(NAME): $(OBJ)
		$(MAKE) -C lib/my/
		cp lib/my/libmy.a .
		gcc -o $(NAME) pong.c libmy.a -I include -lm

clean:
		rm -f $(OBJ)
		rm lib/my/*.o

fclean: clean
		rm -f $(NAME)
		rm libmy.a
		rm lib/my/libmy.a

re:		fclean all
