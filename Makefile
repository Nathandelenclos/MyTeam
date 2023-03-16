##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

PROJECT	=	MyTeams
NAME	=	myTeams

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
	@ make -C ./src/server debug
	@ make -C ./src/client debug
debug: $(NAME)

exp:
	@ export LD_LIBRARY_PATH=./libs/myteams/
	@ printf "$(GREEN)Done$(RESET)\n"

$(NAME): exp
	@ make -C ./libs/linked_list
	@ make -C ./libs/my
	@ make -C ./src/server
	@ make -C ./src/client
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ make -C ./libs/linked_list clean
	@ make -C ./libs/my clean
	@ make -C ./src/server clean
	@ make -C ./src/client clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ make -C ./libs/linked_list fclean
	@ make -C ./libs/my fclean
	@ make -C ./src/server fclean
	@ make -C ./src/client fclean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ $(RM) vgcore.*
	@ $(RM) -r ./doc
	@ printf "$(GREEN)Done$(RESET)\n"

tests_run:	$(TESTOBJ)
	@ echo "tests_run"

re: fclean all
de: fclean debug
