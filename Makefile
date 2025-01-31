# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 20:34:26 by mazeghou          #+#    #+#              #
#    Updated: 2025/01/31 20:36:45 by mazeghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

SRC_PATH	= src/
SRC			= main.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			= -I ./includes/ \
			  -I ./minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(MLX) -lXext -lX11 -lm

$(MLX):
	make -sC $(MLX_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
