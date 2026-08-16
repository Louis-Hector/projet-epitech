##
## EPITECH PROJECT, 2026
## OOP
## File description:
## Makefile
##

CC		=	clang++-20

NAME	=	arcade_sfml.so

SRC		=	Sfml.cpp \
			../../Interface/ALib.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -fPIC -I ../../Interface -g
SOFLAGS = -shared 
SFFLAGS = -lsfml-graphics -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(SOFLAGS) $(SFFLAGS)
			@mv $(NAME) ../../../lib
			@echo "Compilation done"

%.o: %.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

re:			clean all
