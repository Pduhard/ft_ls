# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/13 00:29:26 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2019/03/12 14:45:37 by pduhard-    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	ft_ls

CC			=	gcc
FLAGS		=	-g -Wall -Werror -Wextra
LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INCLUDES	=	includes/ft_ls.h

SRC_PATH	=	./srcs/
BIN_PATH	=	./bin/
LIB_PATH	=	./libft/

SRC			=	main.c			\
				directory.c		\
				files.c			\
				parse_argv.c	\
				parse_options.c	\
				sort.c			\
				merge_sort.c	\
				print.c			\
				detailed.c		\
				fill_buffer.c	\
				file_info.c		\
				date.c			\
				rights.c		\
				free.c			\
				colors.c		\

BIN			=	$(SRC:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))

.PHONY: all clean fclean re lib

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

	@make -C libft

$(NAME): $(LIBS) $(BINS)

	@$(CC) -I $(INCLUDES) $(FLAGS) $(LIB_FLAGS) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME)\" READY]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCLUDES)

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) -I $(INCLUDES) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@echo "${R}[CLEANING $(NAME) BINARIES]"
	@rm -f $(BINS)

fclean: clean

	@echo "\n${R}[REMOVING "libft.a"]"
	@rm -rf $(LIB_PATH)/libft.a
	@echo "\n${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)

re: fclean all
