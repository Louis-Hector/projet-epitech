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
			src/environment_command.c \
			src/create_tab.c \
			src/check_redirection.c \
			src/lead_pipe.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I include -g

all:    $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C lib/my/
		cp lib/my/libmy.a .
		gcc -o $(NAME) $(OBJ) libmy.a $(CFLAGS)

clean:
		rm -f $(OBJ) src/command_fonctions.o src/linked_fonctions.o \
		src\check_absolute_path.c src\create_env.o src\environment_command.o \
		src\create_tab.c src/check_redirection.o src/lead_pipe.o
		$(MAKE) -C lib/my/ clean
		rm -f libmy.a

fclean: clean
		rm -f $(NAME)
		rm lib/my/libmy.a

re:		fclean all
