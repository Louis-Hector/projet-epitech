##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## minishell1
##

NAME	=	mysh

SRC     = 	main.c \
			src/command_fonctions.c \
			src/linked_fonctions.c \
			src/check_absolute_path.c \
			src/create_env.c \
			src/environment_command.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I include -Wall -Wextra -Werror -g

all: 	$(NAME)

all:    $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C lib/my/
		cp lib/my/libmy.a .
		gcc -o $(NAME) $(OBJ) libmy.a $(CFLAGS)

clean:
		rm -f $(OBJ) src/command_fonctions.o src/linked_fonctions.o \
		src\check_absolute_path.c src\create_env.o src\environment_command.o
		$(MAKE) -C lib/my/ clean
		rm -f libmy.a

fclean: clean
		rm -f $(NAME)
		rm lib/my/libmy.a

re:		fclean all
