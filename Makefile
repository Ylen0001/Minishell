NAME = minishell
LIBFT_NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIB_DIR = libft
SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

SRCS = $(addprefix $(SRC_DIR)/, main.c / exec.c)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADER = $(INCLUDES_DIR)/minishell.h

all : $(NAME)

$(NAME) : $(LIB_DIR)/$(LIBFT_NAME) $(OBJS)
	$(CC) $(OBJS) $(LIB_DIR)/$(LIBFT_NAME) -o $(NAME) 

$(LIB_DIR)/$(LIBFT_NAME):
	@if [ ! -e $(LIB_DIR)/$(LIBFT_NAME) ]; then \
		$(MAKE) -C $(LIB_DIR); \
		cp $(LIB_DIR)/$(LIBFT_NAME) .; \
		mv $(LIBFT_NAME) $(NAME); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%_bonus.c | $(OBJ_DIR)
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