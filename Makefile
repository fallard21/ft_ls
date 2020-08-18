# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 21:03:45 by fallard           #+#    #+#              #
#    Updated: 2020/08/18 22:59:11 by fallard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

HEAD_NAME = ft_ls.h
LIB_NAME = libft.a

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = sources/
INC_DIR = includes/
LIB_DIR = libft/

RD = \033[031m
GR = \033[032m
YW = \033[033m
BL = \033[034m
PK = \033[035m
CN = \033[036m
EOC = \033[0m

SRC = main.c \
parsing_arguments.c \
read_dir_info.c \
display_arguments.c \
display_chmod.c \
free_memory.c \
path.c \
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

INCLUDES = -I $(INC_DIR) -I $(LIB_DIR)$(INC_DIR)

all: $(LIBFT) $(NAME) 

$(NAME): $(LIBFT) $(TMP)
	@$(CC) $(CFLAGS) -o $(NAME) $(TMP) $(INCLUDES) -L $(LIB_DIR) -lft
	@printf "$(GR)>> Program $(NAME) created <<\n$(EOC)"

$(LIBFT):
	@make -C $(LIB_DIR)

%.o:%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(TMP)
	@make clean -C $(LIB_DIR)
	@printf "$(YW)$(NAME): $(RD)Object files deleted.\n$(EOC)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@printf "$(YW)$(NAME): $(RD)Program $(NAME) deleted.\n$(EOC)"

re: fclean all
