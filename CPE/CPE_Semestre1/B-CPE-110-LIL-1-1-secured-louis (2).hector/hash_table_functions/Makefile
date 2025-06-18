##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC 	=	create_hashtable.c \
      		delete.c \
      		delete_hashtable.c \
      		dump.c \
      		hash.c \
      		insert.c \
      		search.c

OBJ		=		$(SRC:.c=.o)

NAME	=		libhash.a

all:		$(NAME)

$(NAME):	$(OBJ)
	@gcc -c $(SRC)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:			fclean all
