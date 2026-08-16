##
## EPITECH PROJECT, 2026
## Rush03
## File description:
## Rush03
##

CC		=	clang++-20

SRC		=	main.cpp \
			src/Execution/Execution.cpp \
			src/Parsing/Parsing.cpp \
			src/Interface/AComponent.cpp \
			src/Interface/Links.cpp \
			src/SpecialComponents/FalseComponent.cpp \
			src/SpecialComponents/TrueComponent.cpp \
			src/SpecialComponents/Logger.cpp \
			src/SpecialComponents/Input.cpp \
			src/SpecialComponents/Output.cpp \
			src/SpecialComponents/Clock.cpp \
			src/ElementaryComponents/AndComponent.cpp \
			src/ElementaryComponents/NotComponent.cpp \
			src/ElementaryComponents/OrComponent.cpp \
			src/ElementaryComponents/XorComponent.cpp \
			src/Circuit/Circuit.cpp \
			src/Factory/Factory.cpp \
			src/GatesComponents/Gate4001NOR.cpp \
			src/GatesComponents/Gate4011NAND.cpp \
			src/GatesComponents/Gate4030XOR.cpp \
			src/GatesComponents/Gate4069INVERTER.cpp \
			src/GatesComponents/Gate4071OR.cpp \
			src/GatesComponents/Gate4081AND.cpp \
			src/AdvancedComponents/Advanced4040.cpp \
			src/AdvancedComponents/Advanced4008.cpp \
			src/AdvancedComponents/Advanced4512.cpp \
			src/AdvancedComponents/Advanced4514.cpp  \
			src/AdvancedComponents/Advanced4017.cpp \
			src/AdvancedComponents/Advanced4094.cpp \
			src/AdvancedComponents/Advanced2716.cpp \
			src/AdvancedComponents/Advanced4013.cpp \
			src/AdvancedComponents/Advanced4801.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	nanotekspice

CFLAGS	=	-Wall -Wextra -Werror -I src/Parsing/ -I src/Interface/ -I src/SpecialComponents/ -I src/ElementaryComponents/ -I src/Circuit/ -I src/Factory/ -I src/Execution/ -I src/GatesComponents/ -I src/AdvancedComponents/

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
