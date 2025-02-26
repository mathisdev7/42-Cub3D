/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:24:46 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/25 21:24:46 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dda_algorithm(t_raycast *raycast, t_game *game)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (game->map_info.map[raycast->map_y][raycast->map_x] == '1')
			raycast->hit = 1;
	}
	if (raycast->side == 0)
		raycast->wall_dist = (raycast->side_dist_x - raycast->delta_dist_x);
	else
		raycast->wall_dist = (raycast->side_dist_y - raycast->delta_dist_y);
}
