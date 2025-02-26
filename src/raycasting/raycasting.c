/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:01:23 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 16:24:21 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_line_height(t_raycast *raycast, t_game *game)
{
	raycast->line_height = (int)(game->screen_height / raycast->wall_dist);
	raycast->draw_start_y = game->screen_height / 2 - raycast->line_height / 2;
	if (raycast->draw_start_y < 0)
		raycast->draw_start_y = 0;
	raycast->draw_end_y = raycast->draw_start_y + raycast->line_height;
	if (raycast->draw_end_y >= game->screen_height)
		raycast->draw_end_y = game->screen_height - 1;
	if (raycast->side == 0)
		raycast->wall_x = game->player.pos_y + raycast->wall_dist
			* raycast->ray_dir_y;
	else
		raycast->wall_x = game->player.pos_x + raycast->wall_dist
			* raycast->ray_dir_x;
	raycast->wall_x -= floor(raycast->wall_x);
}

void	store_wall_pixels(t_game *game, int x, t_raycast *raycast, int tex_num)
{
	int			y;
	t_texture	*tex;
	double		step;
	int			color;

	tex = &game->textures[tex_num];
	step = 1.0 * tex->height / raycast->line_height;
	tex->tex_pos = (raycast->draw_start_y - game->screen_height / 2
			+ raycast->line_height / 2) * step;
	y = raycast->draw_start_y;
	while (y < raycast->draw_end_y && y < game->screen_height)
	{
		tex->tex_y = ((int)tex->tex_pos) & (tex->height - 1);
		tex->tex_pos += step;
		if (raycast->tex_x >= 0 && raycast->tex_x < tex->width)
		{
			color = tex->addr[tex->width * tex->tex_y + raycast->tex_x];
			if (color > 0 && x >= 0 && x < game->screen_width && y >= 0)
				game->screen_buffer[y][x] = color;
		}
		y++;
	}
}

int	set_tex_num(t_raycast *raycast)
{
	int	tex_num;

	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x > 0)
			tex_num = EAST;
		else
			tex_num = WEST;
	}
	else
	{
		if (raycast->ray_dir_y > 0)
			tex_num = SOUTH;
		else
			tex_num = NORTH;
	}
	return (tex_num);
}

void	raycasting(t_raycast *raycast, t_game *game)
{
	int	x;
	int	tex_num;

	x = 0;
	tex_num = 0;
	while (x < game->screen_width)
	{
		set_curr_line_values(raycast, x, game);
		init_step_and_side_dist(raycast, game);
		dda_algorithm(raycast, game);
		calc_line_height(raycast, game);
		raycast->tex_x = (int)(raycast->wall_x * game->textures[tex_num].width);
		tex_num = set_tex_num(raycast);
		store_wall_pixels(game, x, raycast, tex_num);
		x++;
	}
}
