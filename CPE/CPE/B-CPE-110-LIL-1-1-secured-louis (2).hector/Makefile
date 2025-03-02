##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME = libhashtable.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

LDFLAGS = hash_table_functions/libhash.a

$(NAME): $(OBJ)
	$(MAKE) -C lib/my/
	$(MAKE) -C libshell/
	$(MAKE) -C hash_table_functions/
	@ar rcT $(NAME) libshell/libshell.a lib/my/libmy.a $(LDFLAGS)

clean:
	$(MAKE) clean -C lib/my/
	$(MAKE) clean -C libshell/
	$(MAKE) clean -C hash_table_functions/

fclean: clean
	rm -f libhashtable.a
	$(MAKE) fclean -C lib/my/
	$(MAKE) fclean -C libshell/
	$(MAKE) fclean -C hash_table_functions/

re: fclean all
