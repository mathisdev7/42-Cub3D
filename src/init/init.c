/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 04:33:25 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/11 20:01:01 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_raycast(t_raycast *raycast)
{
	raycast->camera_x = 0;
	raycast->ray_dir_x = 0;
	raycast->ray_dir_y = 0;
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->side_dist_x = 0;
	raycast->side_dist_y = 0;
	raycast->delta_dist_x = 0;
	raycast->delta_dist_y = 0;
	raycast->wall_dist = 0;
	raycast->wall_x = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->hit = 0;
	raycast->side = 0;
	raycast->line_height = 0;
	raycast->draw_start_y = 0;
	raycast->draw_end_y = 0;
	raycast->tex_x = 0;
}

void	init_screen_buffer(t_game *game)
{
	int	i;

	if (game->screen_buffer)
		free_int_array(game->screen_buffer, game->screen_height);
	game->screen_buffer = malloc(sizeof(int *) * (game->screen_height - 1));
	i = 0;
	while (i < game->screen_height)
	{
		game->screen_buffer[i] = malloc(sizeof(int) * (game->screen_width - 1));
		i++;
	}
}

int	init_textures(t_game *game)
{
	char	*texture_paths[4] = {game->map_info.tab_assets[0],
			game->map_info.tab_assets[1], game->map_info.tab_assets[2],
			game->map_info.tab_assets[3]};
	int		i;
	int		width;
	int		height;

	width = game->tex_size;
	height = game->tex_size;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				texture_paths[i], &width, &height);
		if (!game->textures[i].img)
			return (0);
		game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bits_per_pixel, &game->textures[i].size_line,
				&game->textures[i].endian);
		if (!game->textures[i].addr)
			return (0);
		game->textures[i].width = width;
		game->textures[i].height = height;
		i++;
	}
	return (1);
}

void	draw_pistol(t_game *game)
{
	int		img_width;
	int		img_height;
	int		target_width;
	int		target_height;
	int		start_x;
	int		start_y;
	double	scale_x;
	double	scale_y;
	int		src_x;
	int		src_y;
	int		color;
	int		draw_x;
	int		draw_y;

	img_width = 64;
	img_height = 64;
	target_width = 384;
	target_height = 384;
	start_x = (game->screen_width - target_width) / 2;
	start_y = game->screen_height - target_height;
	scale_x = (double)target_width / img_width;
	scale_y = (double)target_height / img_height;
	for (int y = 0; y < target_height; y++)
	{
		for (int x = 0; x < target_width; x++)
		{
			// Calcul des coordonnées source
			src_x = (int)(x / scale_x);
			src_y = (int)(y / scale_y);
			if (src_x >= 0 && src_x < img_width && src_y >= 0
				&& src_y < img_height)
			{
				color = game->pistol.addr[src_y * img_width + src_x];
				// Vérification des bornes écran
				draw_x = start_x + x;
				draw_y = start_y + y;
				if ((color & 0x00FFFFFF) != 0)
				{
					if (draw_x >= 0 && draw_x < game->screen_width
						&& draw_y >= 0 && draw_y < game->screen_height)
					{
						game->screen_buffer[draw_y][draw_x] = color;
					}
				}
			}
		}
	}
}

void	init_pistol(t_game *game, char *filename)
{
	game->pistol.img = mlx_xpm_file_to_image(game->mlx, filename,
			&game->pistol.width, &game->pistol.height);
	game->pistol.addr = (int *)mlx_get_data_addr(game->pistol.img,
			&game->pistol.bits_per_pixel, &game->pistol.size_line,
			&game->pistol.endian);
}

t_game	*init_game(t_map_info map_info)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->screen_buffer = NULL;
	game->map_info = map_info;
	game->screen_height = 480;
	game->screen_width = 640;
	game->tex_size = 512;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "Cub3d");
	game->player_pos_x = map_info.player_x + 0.5;
	game->player_pos_y = map_info.player_y + 0.5;
	game->player_dir_x = map_info.player_dir_x;
	game->player_dir_y = map_info.player_dir_y;
	game->plane_x = map_info.player_plane_x;
	game->plane_y = map_info.player_plane_y;
	game->sprite.x = map_info.ennemy_sprites[0];
	game->sprite.y = map_info.ennemy_sprites[1];
	game->player_move_x = 0;
	game->player_move_y = 0;
	game->player_rotate = 0;
	init_pistol(game, "./assets/base/gun_idle.xpm");
	init_sprite(game, "./assets/base/guard.xpm");
	init_textures(game);
	init_screen_buffer(game);
	return (game);
}
