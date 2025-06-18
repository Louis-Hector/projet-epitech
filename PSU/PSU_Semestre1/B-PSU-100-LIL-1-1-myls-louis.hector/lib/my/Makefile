##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC 	=		my_put_nbr.c \
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
			option_a.c \
			option_d.c \
			option_l.c \
			option_rmaj.c \
			option_r.c \

OBJ		=		$(SRC:.c=.o)

NAME	=		libmy.a

all:		$(NAME)

$(NAME):	$(OBJ)
			gcc -c $(SRC)
			ar rcs $(NAME) $(OBJ)
			cp my.h ../../include/my.h

copy_lyb:
			cp libmy.a ../

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f ../$(NAME)

re:			fclean all
