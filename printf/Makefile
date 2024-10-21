# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberion <aberion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 14:27:43 by aberion           #+#    #+#              #
#    Updated: 2024/03/04 13:08:52 by aberion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = libftprintf.a

# Compilateur et drapeaux de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Dossiers source et objet
SRC_DIR = src/
OBJ_DIR = obj/

# Fichiers sources et objets
SRCS = ft_printf.c \
       ft_putstr.c \
       ft_print_hex.c \
	   ft_print_int.c \
	   ft_print_uint.c \
	   ft_print_hex_p.c \

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

# Règle all
all: $(NAME)

# Règle pour créer l'exécutable
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Règle pour créer les fichiers objet
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règles supplémentaires
clean:
	rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ] && [ "$(OBJ_DIR)" != "./" ]; then \
		rm -rf $(OBJ_DIR); \
	fi

fclean: clean
	rm -f $(NAME)

re: fclean all

# Règle .PHONY pour éviter les conflits de noms de fichiers
.PHONY: all clean fclean re
