##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CFLAGS  =   -Wall -Wextra -I../../include

NAME = libmy.a

SRC = mini_printf.c \
      my_getnbr.c \
      my_isneg.c \
      my_putchar.c \
      my_put_nbr.c \
      my_putstr.c \
      my_revstr.c \
      my_show_word_array.c \
      my_sort_int_array.c \
      my_strcat.c \
      my_strcmp.c \
      my_strcpy.c \
      my_strdup.c \
      my_strlen.c \
      my_strstr.c \
      my_str_to_word_array.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

all: $(NAME)
	@echo "Building $(NAME)"

$(NAME): $(OBJ)
	@echo "Creating archive $(NAME)"
	@ar rc $(NAME) $(OBJ)
	@echo "Indexing archive $(NAME)"
	@ranlib $(NAME)

clean:
	@echo "Cleaning object files"
	@rm -f $(OBJ)

fclean: clean
	@echo "Cleaning all generated files"
	@rm -f $(NAME)

re: fclean all
