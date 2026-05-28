NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
VPATH=src:src/parsing:src/builtin_cmds:src/execution:src/struct_managers
SRC_DIR = src/
INC_DIR = inc/
INC_FILES = minishell.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))
SRC_FILES = minishell.c lexer.c lst_manager.c lst_token.c utils_parsing.c \
			parsing.c redirection.c cd.c echo.c env.c exit.c export.c \
			pwd.c unset.c exec.c exec_child.c exec_pipe.c env_manager.c \
			error_manager.c expand.c quote_manager.c utils_expand.c heredoc.c \
			exec_manager.c token_manager.c env_builder.c exec_child_utils.c \
			sig_handler.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) -lreadline -I $(INC) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@echo "Making Libft"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

clean :
	@echo "Deleting obj directory"
	@rm -rf $(OBJ_DIR)
	@echo "Deleting libft objects"
	@cd $(LIBFT_DIR) && make clean

fclean : clean
	@echo "Cleaning program name"
	@rm -rf $(NAME)
	@echo "Cleaning Libft"
	@rm -rf $(LIBFT)

re : fclean $(NAME)

.PHONY : all clean fclean re
