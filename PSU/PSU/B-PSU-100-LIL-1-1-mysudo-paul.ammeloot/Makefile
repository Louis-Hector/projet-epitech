##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME = my_sudo

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my/
	$(MAKE) -C sudo_functions/
	gcc -o $(NAME) $(OBJ) main.c lib/my/libmy.a\
	 sudo_functions/libsudo.a -I include -lcrypt

clean:
	$(MAKE) clean -C lib/my/
	$(MAKE) clean -C sudo_functions/
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C lib/my/
	$(MAKE) fclean -C sudo_functions/

re: fclean all

sudo:
	sudo chown root:root $(NAME)
	sudo chmod u+s $(NAME)
