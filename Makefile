NAME = minishell
LIBFT_NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS	= -lreadline -lncurses
LIB_DIR = libft
SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

# SRCS = $(addprefix $(SRC_DIR)/, minishell.c / prompt.c / init.c / parsing.c / workinprog_vect.c)

SRCS = $(addprefix $(SRC_DIR)/, prompt.c / minishell.c / fork.c / garbage_collector.c / path_exec.c / workinprog_vect.c / init.c / parsing.c)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADER = $(INCLUDES_DIR)/minishell.h

all : $(NAME)

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