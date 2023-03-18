##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

PROJECT	=	MyTeams
NAME	=	myTeams

MAKES	=	./libs/network	\
           	./libs/my	\
            ./src/server	\
            ./src/client	\
            ./src/server	\

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	gcc

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug:
	@ $(foreach file, ${MAKES}, make -C $(file) debug;)

exp:
	@ export LD_LIBRARY_PATH=./libs/myteams/
	@ printf "$(GREEN)Done$(RESET)\n"

$(NAME): exp
	@ $(foreach file, ${MAKES}, make -C $(file);)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ $(foreach file, ${MAKES}, make -C $(file) clean;)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(foreach file, ${MAKES}, make -C $(file) fclean;)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ $(RM) vgcore.*
	@ $(RM) -r ./doc
	@ printf "$(GREEN)Done$(RESET)\n"

tests_run:	$(TESTOBJ)
	@ echo "tests_run"

re: fclean all
de: fclean debug

client:
	@ make -C ./libs/linked_list
	@ make -C ./libs/network
	@ make -C ./libs/my
	@ make -C ./src/client
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

server:
	@ make -C ./libs/linked_list
	@ make -C ./libs/network
	@ make -C ./libs/my
	@ make -C ./src/server
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

libs:
	@ make -C ./libs/linked_list
	@ make -C ./libs/network
	@ make -C ./libs/my
	@ make -C ./src/server
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"