# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 20:34:26 by mazeghou          #+#    #+#              #
#    Updated: 2025/02/07 12:07:59 by mazeghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Werror -Wextra -Wall -g3

MLX_PATH    = minilibx-linux/
MLX_NAME    = libmlx.a
MLX         = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH  = libft/
LIBFT_NAME  = libft.a
LIBFT       = $(LIBFT_PATH)$(LIBFT_NAME)

SRC_PATH    = src/
SRC         = main.c parsing/map.c parsing/args.c parsing/cardinals.c \
				parsing/file.c utils/free.c parsing/map_content.c \
				parsing/map_utils.c parsing/map_to_struct.c \
				utils/str.c parsing/map_utils2.c parsing/assets.c \
				parsing/map_validation.c utils/array_utils.c \
				parsing/set.c parsing/colors.c init/init.c render.c parsing/map_validation2.c \
				parsing/player.c parsing/map_last.c raycasting.c

SRCS        = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH    = obj/
OBJ         = $(SRC:.c=.o)
OBJS        = $(addprefix $(OBJ_PATH), $(OBJ))

INC         = -I ./includes/ \
              -I ./minilibx-linux/

RESET       = \033[0m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
MAGENTA     = \033[35m
CYAN        = \033[36m
WHITE       = \033[37m
BOLD        = \033[1m

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/parsing

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling:$(WHITE) $<"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Building executable: $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(MLX) $(LIBFT) -lXext -lX11 -lm
	@echo "$(GREEN)Build successful!$(RESET)"

$(MLX):
	@echo "$(MAGENTA)Building MinilibX...$(RESET)"
	@make -sC $(MLX_PATH) > /dev/null 2>&1

$(LIBFT):
	@echo "$(MAGENTA)Building Libft...$(RESET)"
	@make -sC $(LIBFT_PATH)

clean:
	@printf "$(RED)Cleaning up... $(RESET)"
	@spinner="-+/"; \
	len=10; \
	for i in $$(seq 1 $$len); do \
		char=$$(expr $$i % $$(echo -n $$spinner | wc -m)); \
		printf "\r$(RED)Cleaning up... ${BOLD}%s$(RESET)" "$$(echo -n $$spinner | cut -c$$((char+1)))"; \
		sleep 0.1; \
	done
	@rm -rf $(OBJ_PATH) > /dev/null 2>&1
	@make -C $(MLX_PATH) clean > /dev/null 2>&1
	@make -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@printf "\r$(GREEN)Cleanup complete! ✔$(RESET)\n"

fclean: clean
	@printf "$(RED)Cleaning up... $(RESET)"
	@spinner="-+/"; \
	len=10; \
	for i in $$(seq 1 $$len); do \
		char=$$(expr $$i % $$(echo -n $$spinner | wc -m)); \
		printf "\r$(RED)Cleaning up... ${BOLD}%s$(RESET)" "$$(echo -n $$spinner | cut -c$$((char+1)))"; \
		sleep 0.1; \
	done
	@rm -rf $(NAME) > /dev/null 2>&1
	@make -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@printf "\r$(GREEN)Cleanup complete! ✔$(RESET)\n"

re: fclean all

.PHONY: all re clean fclean
