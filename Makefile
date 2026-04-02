NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src/
FILES = minishell.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ) : $(SRC) | $(OBJ_DIR)
	cd $(OBJ_DIR) && $(CC) $(CFLAGS) -c $(addprefix ../, $(SRC))

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
