##
## EPITECH PROJECT, 2026
## OOP
## File description:
## Makefile
##

CC      =   clang++-20

NAME    =   arcade

SRC     =   main.cpp \
            src/Parsing/Parsing.cpp \
            src/Interface/ALib.cpp \
			src/Encapsulation/Libdl.cpp \
			src/Core/Core.cpp

OBJ     =   $(SRC:.cpp=.o)

CFLAGS  =   -Wall -Wextra -Werror -fPIC -g -I src/Parsing/ -I src/Interface/ -I src/Graphical/ -I src/Encapsulation/ \
			-I src/Core/

LDFLAGS =   -ldl -rdynamic

all:        graphicals games core

core:       $(OBJ)
	@mkdir -p lib
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "Core compilation done"

games:
	@mkdir -p lib
	@$(MAKE) -C src/Games/Snake all >/dev/null
	@$(MAKE) -C src/Games/Minesweeper all >/dev/null
	@$(MAKE) -C src/Games/Tetris all >/dev/null

graphicals:
	@mkdir -p lib
	@$(MAKE) -C src/Graphical/SDL2 all >/dev/null
	@$(MAKE) -C src/Graphical/Ncurses all >/dev/null
	@$(MAKE) -C src/Graphical/Sfml all>/dev/null

%.o:        %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C src/Graphical/SDL2 clean >/dev/null
	@$(MAKE) -C src/Graphical/Ncurses clean >/dev/null
	@$(MAKE) -C src/Graphical/Sfml clean >/dev/null
	@$(MAKE) -C src/Games/Snake clean >/dev/null
	@$(MAKE) -C src/Games/Minesweeper clean >/dev/null
	@$(MAKE) -C src/Games/Tetris clean >/dev/null
	@echo "Cleaning done"

fclean:     clean
	@rm -f $(NAME)
	@find lib -name "*.so" -delete 2>/dev/null || true
	@echo "Full cleaning done."

re:         fclean all

.PHONY: all core games graphicals clean fclean re
