##
## EPITECH PROJECT, 2026
## OOP
## File description:
## Makefile
##

CC		=	clang++-20

NAME	=	arcade_sdl2.so

SRC		=	SDL2.cpp \
			../../Interface/ALib.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -fPIC -I ../../Interface
SOFLAGS = -shared 
SDLFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(SOFLAGS) $(SDLFLAGS)
			@mv $(NAME) ../../../lib
			@echo "Compilation done"

%.o: %.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

re:			clean all
