##
## EPITECH PROJECT, 2018
## libmy
## File description:
## Makefile
##

PROJECT	=	list
NAME	=	../myteams/liblist.a

OBJS	=	$(SRCS:.c=.o)

################################################################################

#CFLAGS	+=	-W -Wall -Wextra

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

# ---------------------------------------------------------------------------- #
#  Modules                                                                     #
# ---------------------------------------------------------------------------- #

SRCS	+=	$(shell find . -type f -name "*.c")
HEADS 	= $(shell find . -type f -name "*.h")

CFLAGS	=	-g

################################################################################

all: $(NAME)

debug: CFLAGS += -g3
debug: $(NAME)

$(NAME): prebuild $(OBJS)
	@ cp $(HEADS) ../../include
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Building $(NAME)"
	@ (ar rc $(NAME) $(OBJS) && ranlib $(NAME)) && \
	  (printf "$(GREEN)Done$(RESET)\n" ; exit 0) || \
	  (printf "$(RED)Fail$(RESET)\n" ; exit 1)

prebuild:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug

.c.o:
	@ $(CC) -c $< -o $@ $(CFLAGS) && \
	  ($(PRINT) "  $(GREEN)[OK]$(CYAN)  %b$(RESET)\n" $<) || \
	  ($(PRINT) "  $(RED)[XX]$(CYAN)  %b$(RESET)\n" $< ; exit 1)

.PHONY: all debug $(NAME) prebuild clean fclean re de .c.o
