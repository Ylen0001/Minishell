# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberion <aberion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:20:23 by aberion           #+#    #+#              #
#    Updated: 2023/11/20 19:39:46 by aberion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBC =	ft_bzero.c ft_isalnum.c ft_isalpha.c ft_strnstr.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_atoi.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strdup.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_memcmp.c ft_calloc.c \
		ft_strjoin.c

ADDITIONAL =	ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c

BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c 

SRCS = ${LIBC} ${ADDITIONAL}

SRCSALL = ${LIBC} ${ADDITIONAL} ${BONUS}

OBJS = ${SRCS:.c=.o}

OBJSALL = ${SRCSALL:.c=.o} 

LIB = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

HEADER_FILE = libft.h

%.o: %.c
		${CC} ${CFLAGS} -o $@ -c $<
		
${LIB}:	${OBJS}
		ar -rsc ${LIB} ${OBJS}

bonus:	${OBJSALL}
		ar -rsc ${LIB} ${OBJSALL}

all: 	${LIB}

clean:	
		rm -f ${OBJSALL}

fclean:	clean;
		rm -f ${LIB}

re:	fclean all

.PHONY: all clean fclean re bonus
