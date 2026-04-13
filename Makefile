NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
VPATH=src:src/lexer
SRC_DIR = src/
INC_DIR = inc/
INC_FILES = minishell.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))
SRC_FILES = minishell.c lexer.c lst_manager.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline -I $(INC) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

clean :
	rm -rf $(OBJ_DIR)
	cd $(LIBFT_DIR) && make clean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re : fclean $(NAME)

.PHONY : all clean fclean re
