##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME    = my_radar

SRC     = 	src/my_radar.c \
			src/read_script.c \
			src/create_airplane.c \
			src/print_time.c \

OBJ     = $(SRC:.c=.o)

LFLAGS  = -I include libmy.a -lcsfml-graphics -lcsfml-system \
          -lcsfml-window -lm

all:    $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my/
	cp lib/my/libmy.a .
	gcc -o $(NAME) $(SRC)  $(LFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ) src/read_script.o src/create_airplane.o src\print_time.o
	$(MAKE) -C lib/my/ clean
	rm -f libmy.a

fclean: clean
	rm -f $(NAME)
	rm -f lib/my/libmy.a

re: fclean all
