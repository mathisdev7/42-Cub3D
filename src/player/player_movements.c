/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:54:18 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/25 20:54:18 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVESPEED;
	new_y = player->pos_y + player->dir_y * MOVESPEED;
	if (map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}

void	move_backward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVESPEED;
	new_y = player->pos_y - player->dir_y * MOVESPEED;
	if (map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}

void	move_right(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_y * MOVESPEED;
	new_y = player->pos_y + player->dir_x * MOVESPEED;
	if (map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}

void	move_left(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_y * MOVESPEED;
	new_y = player->pos_y - player->dir_x * MOVESPEED;
	if (map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}
