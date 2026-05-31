NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INC_FILES = minishell.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = inc/
EXEC_DIR := execution/
BUILT_DIR := builtin_cmds/
PARSER_DIR := parsing/
STRUCT_DIR := struct_managers/

SRC_FILES := $(SRC_DIR)minishell.c \
			 $(SRC_DIR)sig_handler.c \
			 $(SRC_DIR)$(PARSER_DIR)parsing.c \
			 $(SRC_DIR)$(PARSER_DIR)utils_parsing.c \
			 $(SRC_DIR)$(PARSER_DIR)redirection.c \
			 $(SRC_DIR)$(PARSER_DIR)lexer.c \
			 $(SRC_DIR)$(PARSER_DIR)expand.c \
			 $(SRC_DIR)$(PARSER_DIR)utils_expand.c \
			 $(SRC_DIR)$(PARSER_DIR)lst_manager.c \
			 $(SRC_DIR)$(PARSER_DIR)lst_token.c \
			 $(SRC_DIR)$(PARSER_DIR)quote_manager.c \
			 $(SRC_DIR)$(PARSER_DIR)heredoc.c \
			 $(SRC_DIR)$(PARSER_DIR)error_manager.c \
			 $(SRC_DIR)$(EXEC_DIR)exec.c \
			 $(SRC_DIR)$(EXEC_DIR)exec_child.c \
			 $(SRC_DIR)$(EXEC_DIR)exec_child_utils.c \
			 $(SRC_DIR)$(EXEC_DIR)exec_pipe.c \
			 $(SRC_DIR)$(BUILT_DIR)cd.c \
			 $(SRC_DIR)$(BUILT_DIR)echo.c \
			 $(SRC_DIR)$(BUILT_DIR)env.c \
			 $(SRC_DIR)$(BUILT_DIR)exit.c \
			 $(SRC_DIR)$(BUILT_DIR)export.c \
			 $(SRC_DIR)$(BUILT_DIR)pwd.c \
			 $(SRC_DIR)$(BUILT_DIR)unset.c \
			 $(SRC_DIR)$(STRUCT_DIR)env_builder.c \
			 $(SRC_DIR)$(STRUCT_DIR)env_manager.c \
			 $(SRC_DIR)$(STRUCT_DIR)exec_manager.c \
			 $(SRC_DIR)$(STRUCT_DIR)token_manager.c \

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))


all : header $(NAME)

header:
	@echo ""
	@printf "%s\n" '   /\\,/\\,                   ,,          ,, ,, '
	@printf "%s\n" "  /| || ||   '        '       ||          || || "
	@printf "%s\n" '  || || ||  \\ \\/\\ \\  _-_, ||/\\  _-_  || || '
	@printf "%s\n" '  ||=|= ||  || || || || ||_.  || || || \\ || || '
	@printf "%s\n" ' ~|| || ||  || || || ||  ~ || || || ||/   || || '
	@printf "%s\n" '  |, \\,\\, \\ \\ \\ \\ ,-_-  \\ |/ \\,/  \\ \\ '
	@printf "%s\n" ' _-                             _/              '
	@echo ""
	@echo ""

$(NAME) : $(OBJ) $(LIBFT)
	@echo "𖤐⭒๋࣭ ⭑ Compilation of Minishell finished !"
	@${CC} ${CFLAGS} -lreadline -I ${INC} -o ${NAME} ${OBJ} ${LIBFT}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -I $(INC_DIR) -c $< -o $@

$(LIBFT) :
	@echo "𖤐⭒๋࣭ ⭑ Compilation of libft finished !"
	@make --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

clean :
	@echo "👉🗑️ Cleaning all .o files !"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean : clean
	@echo "💥 Deleting Minishell"
	@rm -rf $(NAME)
	@echo "💥 Deleting Libft"
	@rm -rf $(LIBFT)

re : header fclean $(NAME)

.PHONY : all clean fclean re
