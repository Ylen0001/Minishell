

# Compilateur et regles de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fPIE

# Tout les .c qu'on souhaite compiler
SOURCES =  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c get_next_line.c get_next_line_utils.c \
	ft_printf_char.c ft_printf_hex.c ft_printf_int.c ft_printf_str.c \
	ft_putchar_count.c ft_putstr_count.c ft_printf.c \
	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c \
	ft_lstmap_bonus.c ft_lstsize_bonus.c # get_next_line_bonus.c \
	
# Tout les .c qu'on souhaite compiler en .o
OBJECTS = $(SOURCES:.c=.o)

# .h qu'on souhaite intégrer à l'éxécutable
HEADER = libft.h get_next_line.h get_next_line_bonus.h ft_printf.h

# nom de la bibliotheque / du projet
TARGET = libft.a

# Tout les .c bonus qu.on souhaite compiler en .o
OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

AR = ar rc

# Demande à tout compiler lorsque l'on utilisera la commande make
all: $(TARGET)

so:
	$(CC) -fPIC $(CFLAGS) -c $(SRCS_BONUS) 
	$(CC) -shared -o libft.so $(OBJECTS_BONUS) 

# règles de compilation des .c en .o
main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle BONUS

bonus: $(OBJECTS_BONUS) 
	$(AR) $(TARGET) $(OBJECTS_BONUS)

# règles de compilation de l'éxécutable
$(TARGET): $(OBJECTS)
	ar rcs $@ $^

# Nettoyer les .o compilés
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BONUS)

# Commande pour nettoyer les .o et l'éxécutable
fclean: clean
	rm -f $(TARGET)
	rm -f $(EXEC)

# Re-Build tout le projet
re: fclean all

# La commande PHONY indique au programme de ne pas prendre en compte
# les commandes suivantes comme des objets utiles à la compilation
.PHONY: all clean fclean re

