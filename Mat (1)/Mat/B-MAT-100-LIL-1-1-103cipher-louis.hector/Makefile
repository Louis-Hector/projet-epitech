##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## gcc my_printf
##

NAME	=	103cipher

OBJ		=	$(SRC:.c=.o)

DOSSIER 	= 	cipher.c

all: 	$(NAME)


$(NAME): $(OBJ)
		gcc -o $(NAME) $(DOSSIER) -I include -lm

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all
