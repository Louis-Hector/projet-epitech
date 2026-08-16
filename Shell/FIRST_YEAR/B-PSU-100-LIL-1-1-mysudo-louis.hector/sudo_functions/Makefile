##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC 	=	sudo_passwd.c \
			is_perm.c \
			check_flags.c \

OBJ		=		$(SRC:.c=.o)

NAME	=		libsudo.a

all:		$(NAME)

$(NAME):	$(OBJ)
	@gcc -c $(SRC)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all
