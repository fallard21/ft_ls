# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tima <tima@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 17:12:55 by tima              #+#    #+#              #
#    Updated: 2020/07/09 00:02:36 by tima             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

HEAD_NAME = ft_ls.h
LIB_NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = sources/
INC_DIR = includes/
LIB_DIR = libft/

SRC = main.c ls_mem.c \
ls_parse_args.c \
ls_chmod.c \
ls_memory.c \
ls_sort.c \
ls_max_width.c \
ls_time.c \
print.c

TMP = $(addprefix $(SRC_DIR), $(SRC:.c=.o))
HEADER = $(addprefix $(INC_DIR), $(HEAD_NAME))
LIBFT = $(addprefix $(LIB_DIR), $(LIB_NAME))

INCLUDES = -I $(INC_DIR) -I libft/includes

all: $(TMP)
	$(CC) $(TMP) $(INCLUDES) libft/libft.a

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TMP)

re: clean all
