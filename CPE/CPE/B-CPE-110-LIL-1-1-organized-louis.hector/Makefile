##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## gcc my_printf
##

NAME	=	organized

OBJ		=	$(SRC:.c=.o)

all: 	$(NAME)

CFLAGS += libshell/libshell.a libmy.a -I include

$(NAME): $(OBJ)
		$(MAKE) -C lib/my/
		cp lib/my/libmy.a .
		gcc -o $(NAME) organized.c -L libshell/shell.h $(CFLAGS)

clean:
		rm -f $(OBJ)
		rm lib/my/*.o

fclean: clean
		rm -f $(NAME)
		rm libmy.a
		rm lib/my/libmy.a

re:		fclean all
