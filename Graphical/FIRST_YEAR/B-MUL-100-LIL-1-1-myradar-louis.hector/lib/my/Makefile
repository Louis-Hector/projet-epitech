##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC 	=		my_put_nbr.c \
			my_putstr.c \
			my_strlen.c \
			my_putchar.c \
			mini_printf.c \
			my_strcmp.c \
			my_str_to_word_array.c \
			my_show_word_array.c \
			my_getnbr.c \

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
