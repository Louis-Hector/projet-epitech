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
			my_str_to_word_array.c \
			make_header.c \
			search_task.c \
			make_the_cpu.c \
			make_lower_section_stat.c \
			make_lsection_status.c \
			print_ltime.c \
			print_first_lines.c \
			print_percent_mem.c \


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
