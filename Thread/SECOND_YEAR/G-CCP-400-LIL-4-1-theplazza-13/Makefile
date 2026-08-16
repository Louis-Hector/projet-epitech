##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

CC = g++

SRC = 	main.cpp \
		src/Parsing/Parsing.cpp \
		src/Shell/Shell.cpp \
		src/Encapsulate/Mutex.cpp \
		src/Encapsulate/Processus.cpp  \
		src/Encapsulate/Thread.cpp \
		src/Encapsulate/ScopedLock.cpp \
		src/Encapsulate/CondVar.cpp \
		src/Encapsulate/SafeQueue.cpp \
		src/IPCMessage/IPC.cpp \
		src/IPCMessage/IPCMessage.cpp \
        src/Kitchen/Kitchen.cpp \
		src/Kitchen/Stock.cpp \
		src/Reception/Reception.cpp \
		src/Log/Log.cpp \
		src/Interface/APizza.cpp \
		src/Pizza/Margarita.cpp \
		src/Pizza/Americana.cpp \
		src/Pizza/Regina.cpp \
		src/Pizza/Fantasia.cpp \
		src/Factory/Factory.cpp

NAME = plazza

OBJ     =   $(SRC:.cpp=.o)

CFLAGS  =   -Wall -Wextra -Werror -g -fPIC -pthread -I src -I src/Parsing -I src/Shell -I src/Encapsulate -I src/Kitchen -I src/Log -I src/Interface -I src/Pizza -I src/Factory -I src/Reception -I src/IPCMessage

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)
			@echo "Compilation done"

%.o:		%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@rm -f $(NAME)
			@echo "Full cleaning done."

re:			fclean all

