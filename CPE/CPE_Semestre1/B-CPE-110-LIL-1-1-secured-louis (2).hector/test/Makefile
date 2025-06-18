


##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = test

LIBRARY = ../libhashtable.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L../ -lhashtable -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -I ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all

