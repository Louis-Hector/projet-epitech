##
## EPITECH PROJECT, 2026
## OOP
## File description:
## Makefile
##

CC		=	clang++-20

NAME	=	arcade_tetris.so

SRC		=	Tetris.cpp \
			../../Interface/ALib.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -fPIC -I ../../Interface
SOFLAGS = -shared

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(SOFLAGS)
			@mv $(NAME) ../../../lib
			@echo "Compilation done"

%.o: %.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

re:			clean all
