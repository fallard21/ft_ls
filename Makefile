# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 21:03:45 by fallard           #+#    #+#              #
#    Updated: 2020/08/15 04:57:55 by fallard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ls

HEAD_NAME = ft_ls.h
LIB_NAME = libft.a

CC = gcc -g# -fsanitize=address
CFLAGS = 

SRC_DIR = sources/
INC_DIR = includes/
LIB_DIR = libft/

SRC = main.c \
parsing_arguments.c \
read_dir_info.c \
display_arguments.c \
display_chmod.c \
free_memory.c \
do_ls.c \
sorting.c \
sort_types.c \
calculate_width.c \
column_bonus_1.c \
column_bonus_2.c \
display.c \
display_extended.c \
display_other.c

TMP = $(addprefix $(SRC_DIR), $(SRC:.c=.o))
HEADER = $(addprefix $(INC_DIR), $(HEAD_NAME))
LIBFT = $(addprefix $(LIB_DIR), $(LIB_NAME))

INCLUDES = -I $(INC_DIR) -I libft/includes

all: $(NAME) 

$(NAME): $(TMP)
	$(CC) -o $(NAME) $(TMP) $(INCLUDES) -L $(LIB_DIR) -lft

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TMP)

fclean: clean
	rm -f $(NAME)

re: fclean all
