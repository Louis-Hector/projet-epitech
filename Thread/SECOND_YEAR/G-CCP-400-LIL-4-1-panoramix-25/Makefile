##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

SRC		=	main.c \
			src/core.c

NAME = panoramix

OBJ = $(SRC:.c=.o)

CC = epiclang

CFLAGS = -std=gnu17 -Wall -Wextra -Werror -g -I include/

THFLAGS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)  $(THFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:		fclean all
