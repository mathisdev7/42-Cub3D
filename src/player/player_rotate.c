/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:52:48 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/25 20:52:48 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROTSPEED) - player->dir_y
		* sin(ROTSPEED);
	player->dir_y = old_dir_x * sin(ROTSPEED) + player->dir_y * cos(ROTSPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROTSPEED) - player->plane_y
		* sin(ROTSPEED);
	player->plane_y = old_plane_x * sin(ROTSPEED) + player->plane_y
		* cos(ROTSPEED);
}

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROTSPEED) - player->dir_y
		* sin(-ROTSPEED);
	player->dir_y = old_dir_x * sin(-ROTSPEED) + player->dir_y * cos(-ROTSPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROTSPEED) - player->plane_y
		* sin(-ROTSPEED);
	player->plane_y = old_plane_x * sin(-ROTSPEED) + player->plane_y
		* cos(-ROTSPEED);
}
