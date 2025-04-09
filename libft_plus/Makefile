# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/03/21 17:58:00 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

NAME := libft_plus.a
SRC_DIR := src
HEADERS_DIR := include

LIBFT_DIR := libft
LIBFT_SRC := ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isprint.c ft_isascii.c \
             ft_toupper.c ft_tolower.c \
             ft_strlen.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c \
             ft_strncmp.c ft_strnstr.c ft_striteri.c ft_strmapi.c \
    		 ft_atoi.c ft_itoa.c \
			 ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			 ft_strdup.c ft_strtrim.c ft_substr.c \
			 ft_memset.c ft_bzero.c \
			 ft_strjoin.c ft_split.c \
			 ft_calloc.c \
			 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			 ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			 ft_lstlast.c ft_lstadd_back.c \
			 ft_lstdelone.c ft_lstclear.c \
			 ft_lstiter.c ft_lstmap.c
LIBFT_OBJ := $(LIBFT_SRC:%.c=$(SRC_DIR)/$(LIBFT_DIR)/%.o)

DPRINTF_DIR := ft_dprintf
DPRINTF_SRC := ft_dprintf.c \
			   increase_print_count.c \
			   print_chars.c \
			   print_int.c \
			   print_ptr.c \
			   print_hex.c
DPRINTF_OBJ := $(DPRINTF_SRC:%.c=$(SRC_DIR)/$(DPRINTF_DIR)/%.o)

SET_NEXT_LINE_DIR := set_next_line
SET_NEXT_LINE_SRC := set_next_line.c \
		  			 set_next_line_utils.c
SET_NEXT_LINE_OBJ := $(SET_NEXT_LINE_SRC:%.c=$(SRC_DIR)/$(SET_NEXT_LINE_DIR)/%.o)

SRC := $(LIBFT_SRC) $(DPRINTF_DIR) $(SET_NEXT_LINE_SRC)
OBJ := $(LIBFT_OBJ) $(DPRINTF_OBJ) $(SET_NEXT_LINE_OBJ)

COMPILE_FLAGS := -Wall -Wextra -Werror -I. -I$(HEADERS_DIR)

%.o: %.c
	$(CC) $(COMPILE_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

.PHONY: all clean fclean re neat
