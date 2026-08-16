##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

LIB_MYTEAMS_DIR = ../libs/myteams
NAME = ../myteams_server
CC = clang++-20
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I src/Parsing_server/ -I src/Core/ -I src/Encapsulate/ -I src/Client/ -I src/Server_Command -I src/LoadSave -I src/LoadSave/DataType -I ../libs/myteams
LDFLAGS = -L$(LIB_MYTEAMS_DIR)
LDLIBS = -l myteams -l uuid

SRC = 	main.cpp \
			src/Parsing_server/Parsing_server.cpp \
			src/Core/Core.cpp \
			src/Encapsulate/NetEncoder.cpp \
			src/LoadSave/LoadSave.cpp \
			src/LoadSave/DataType/ChannelData.cpp \
			src/LoadSave/DataType/PrivateMessageData.cpp \
			src/LoadSave/DataType/ReplyData.cpp \
			src/LoadSave/DataType/SubscriptionData.cpp \
			src/LoadSave/DataType/TeamData.cpp \
			src/LoadSave/DataType/ThreadData.cpp \
			src/LoadSave/DataType/UserData.cpp \
			src/Client/Client.cpp \
			src/Server_Command/Server_Command.cpp

OBJ = $(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
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