##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## nice Makefile
##

SRC		=	src/error_handling.c \
			src/body.c \
			src/header.c \
			src/label.c \
			src/body_label.c \
			src/main.c \
			src/my_strrchr.c

NAME	=	asm

OBJ	=	$(SRC:.c=.o)

all :
		$(MAKE) -C lib/my/
		gcc -o $(NAME) $(SRC) -Iinclude -Llib/my -lmy -lcrypt

clean :
		rm -f $(OBJ)
		rm -f *.gcda
		rm -f *.gcno

fclean :	clean
			make -C lib/my/ clean
			rm -f $(NAME)
			rm -rf *.o
			rm -rf lib/my/libmy.a

re :	fclean all
