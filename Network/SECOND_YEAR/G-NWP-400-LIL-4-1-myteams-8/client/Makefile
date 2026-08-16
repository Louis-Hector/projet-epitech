##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

LIB_MYTEAMS_DIR = ../libs/myteams
NAME = ../myteams_cli
CC = clang++-20
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I src/Parsing_client/ -I ../libs/myteams
LDFLAGS = -L$(LIB_MYTEAMS_DIR)
LDLIBS = -lmyteams

SRC = 	main.cpp \
    	src/Parsing_client/Parsing_client.cpp \
		src/Parsing_client/Handle_output.cpp

OBJ = $(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):    $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo "Compilation done"

%.o:        %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Cleaning done"

fclean:     clean
	@rm -f $(NAME)
	@echo "Full cleaning done."

re:         fclean all

.PHONY:     all clean fclean re