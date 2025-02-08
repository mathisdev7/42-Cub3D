/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:01:23 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/09 00:43:57 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_step_and_side_dist(t_raycast *raycast, t_game *game)
{
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (game->player_pos_x - raycast->map_x)
			* raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - game->player_pos_x)
			* raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (game->player_pos_y - raycast->map_y)
			* raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - game->player_pos_y)
			* raycast->delta_dist_y;
	}
}

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

void	set_curr_line_values(t_raycast *raycast, int x, t_game *game)
{
	raycast->hit = 0;
	raycast->side = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->camera_x = 2 * x / (double)game->screen_width - 1;
	raycast->ray_dir_x = game->player_dir_x + game->plane_x * raycast->camera_x;
	raycast->ray_dir_y = game->player_dir_y + game->plane_y * raycast->camera_x;
	raycast->map_x = (int)game->player_pos_x;
	raycast->map_y = (int)game->player_pos_y;
	raycast->delta_dist_x = (raycast->ray_dir_x == 0) ? 1e30 : fabs(1
			/ raycast->ray_dir_x);
	raycast->delta_dist_y = (raycast->ray_dir_y == 0) ? 1e30 : fabs(1
			/ raycast->ray_dir_y);
}

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
		raycast->wall_x = game->player_pos_y + raycast->wall_dist
			* raycast->ray_dir_y;
	else
		raycast->wall_x = game->player_pos_x + raycast->wall_dist
			* raycast->ray_dir_x;
	raycast->wall_x -= floor(raycast->wall_x);
}

void	store_wall_pixels(t_game *game, int x, t_raycast *raycast)
{
	int			y;
	t_texture	*tex;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;

	tex = &game->textures[raycast->side];
	step = 1.0 * tex->height / raycast->line_height;
	tex_pos = (raycast->draw_start_y - game->screen_height / 2
			+ raycast->line_height / 2) * step;
	y = raycast->draw_start_y;
	while (y < raycast->draw_end_y && y < game->screen_height)
	{
		tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += step;
		if (raycast->tex_x >= 0 && raycast->tex_x < tex->width)
		{
			color = tex->addr[tex->width * tex_y + raycast->tex_x];
			if (raycast->side == 1)
				color = (color >> 1) & 8355711;
			if (color > 0 && x >= 0 && x < game->screen_width && y >= 0)
				game->screen_buffer[y][x] = color;
		}
		y++;
	}
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
		if (raycast->side == 0 && raycast->ray_dir_x > 0)
			raycast->tex_x = game->textures[tex_num].width - raycast->tex_x - 1;
		if (raycast->side == 1 && raycast->ray_dir_y < 0)
			raycast->tex_x = game->textures[tex_num].width - raycast->tex_x - 1;
		store_wall_pixels(game, x, raycast);
		x++;
	}
}
