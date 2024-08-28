NAME = minishell
LIBFT_NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS	= -lreadline -lncurses
LIB_DIR = libft
SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

SRCS = $(addprefix $(SRC_DIR)/, minishell.c / builtin_ry.c / cd.c / built_in.c / pwd.c / echo.c / path_exec.c / lil_gnl.c / here_doc_handler.c / signal.c / prompt.c / init.c / parsing.c / workinprog_vect.c / garbage_collector.c)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADER = $(INCLUDES_DIR)/minishell.h

all : $(NAME)

DEF_COLOR		:= \033[0;39m
GRAY			:= \033[0;90m
RED				:= \033[0;91m
GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
MAGENTA			:= \033[0;95m
CYAN			:= \033[0;96m
WHITE			:= \033[0;97m
RESET			:= \033[0m

$(NAME) : $(LIB_DIR)/$(LIBFT_NAME) $(OBJS)
	$(CC) $(OBJS) $(LIB_DIR)/$(LIBFT_NAME) $(CFLAGS) $(LDFLAGS) -o $(NAME) 

$(LIB_DIR)/$(LIBFT_NAME):
	@if [ ! -e $(LIB_DIR)/$(LIBFT_NAME) ]; then \
		$(MAKE) -C $(LIB_DIR); \
		cp $(LIB_DIR)/$(LIBFT_NAME) .; \
		mv $(LIBFT_NAME) $(NAME); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean 
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus

all : ascii_art

ascii_art:
	@echo "$(CYAN)"
	@cat logo.txt
	@echo "$(RESET)"