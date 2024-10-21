NAME_SERVER = server
NAME_CLIENT = client
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_SERVER = server.c server_utils.c
SRCS_CLIENT = client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
LIBFT = libft/libft.a
PRINTF_DIR = printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(LIBFT) $(PRINTF_LIB)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT) $(PRINTF_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make clean -C libft
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make fclean -C libft
	make fclean -C $(PRINTF_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
