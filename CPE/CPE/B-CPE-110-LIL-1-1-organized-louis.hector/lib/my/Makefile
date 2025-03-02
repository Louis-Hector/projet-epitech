##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC 	=	my_put_nbr.c \
			my_putstr.c \
			my_revstr.c \
			my_strlen.c \
			my_putchar.c \
			my_getnbr.c \
			my_strdup.c \
			my_strcpy.c \
			my_strcat.c \
			my_strcmp.c \
			mini_printf.c \
			my_show_word_array.c \
			make_add.c \
			make_del.c \
			make_sort.c \
			make_reverse.c \


OBJ		=		$(SRC:.c=.o)

NAME	=		libmy.a

all:		$(NAME)

$(NAME):	$(OBJ)
			gcc -c $(SRC)
			ar rcs $(NAME) $(OBJ)

copy_lyb:
			cp libmy.a ../

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f ../$(NAME)

re:			fclean all
