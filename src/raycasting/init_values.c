/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:24:04 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/25 21:24:04 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_curr_line_values(t_raycast *raycast, int x, t_game *game)
{
	raycast->hit = 0;
	raycast->side = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->camera_x = 2 * x / (double)game->screen_width - 1;
	raycast->ray_dir_x = game->player.dir_x + game->player.plane_x
		* raycast->camera_x;
	raycast->ray_dir_y = game->player.dir_y + game->player.plane_y
		* raycast->camera_x;
	raycast->map_x = (int)game->player.pos_x;
	raycast->map_y = (int)game->player.pos_y;
	raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
}

void	init_step_and_side_dist(t_raycast *raycast, t_game *game)
{
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (game->player.pos_x - raycast->map_x)
			* raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - game->player.pos_x)
			* raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (game->player.pos_y - raycast->map_y)
			* raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - game->player.pos_y)
			* raycast->delta_dist_y;
	}
}
