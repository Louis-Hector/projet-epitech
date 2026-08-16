##
## EPITECH PROJECT, 2025
## makefile
## File description:
## makefile for 42sh
##

SRC = 	src/main.c 								\
		src/builtins/browse_builtin.c 			\
		src/builtins/cd.c						\
		src/builtins/env_utilities.c			\
		src/builtins/env.c 						\
		src/builtins/exit.c 					\
		src/builtins/from_array_to_list.c 		\
		src/builtins/from_list_to_array.c 		\
		src/builtins/history.c 					\
		src/builtins/setenv.c 					\
		src/builtins/unsetenv.c 				\
		src/parsing/parsing.c 					\
		src/free_functions/free_parsing.c		\
		src/parsing/add_spaces.c				\
		src/parsing/init_redir_op.c				\
		src/parsing/handle_redir_op.c 			\
		src/history/file_history.c 				\
		src/history/browse_history.c 			\
		src/history/check_input.c				\
		src/history/key_termios.c				\
		src/create_files/create_history_files.c \
		src/free_functions/free_history.c 		\
		src/shell_command/handle_shell_commands.c \
		src/operator/redirection.c				\
		src/globbins/globbins.c					\
		lib/my_str_to_word_array.c 				\
		src/builtins/handle_prompt.c			\
		src/easter_egg/easter_egg.c 			\
		src/execution_and_check/check.c 		\
		src/execution_and_check/execute.c		\
		src/builtins/script_commands/which.c	\
		src/builtins/script_commands/foreach.c  \
		src/builtins/script_commands/parsing_scripts.c \
		src/builtins/script_commands/where.c  	\
		src/builtins/script_commands/repeat.c   \
		src/operator/pipe.c						\
		src/alias/alias.c						\
		src/utilities/get_array_size.c 			\
		src/history/auto_complete.c			    \
		src/operator/verif_pipe.c 			    \

NAME = 42sh

OBJ = $(SRC:.c=.o)

CFLAGS = -Iinclude -Wall -Wextra -Werror -g

CFLAGS_TEST = -Iinclude -fprofile-arcs -ftest-coverage -lcriterion -Iinclude

TEST_OBJ = $(filter-out src/main.o, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete
	find . -name "*.o" -type f -delete

fclean: clean
	rm -f $(NAME)

re:		fclean all

debug:
	gcc -Wall -Wextra -Werror -g -o $(NAME) $(OBJ) $(CFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./42sh

tests_run: fclean
	$(MAKE) OBJ="$(TEST_OBJ)" CFLAGS="$(CFLAGS_TEST)" $(TEST_OBJ)
	gcc -o unit_tests tests/test_shell.c $(TEST_OBJ) $(CFLAGS_TEST)
	./unit_tests | true
	rm unit_tests | true
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete
	find . -name "*.o" -type f -delete
