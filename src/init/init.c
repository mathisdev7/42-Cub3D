/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 04:33:25 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/06 04:33:25 by nopareti         ###   ########.fr       */
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

void init_screen_buffer(t_game *game)
{
    int i;
    
	if (game->screen_buffer)
		free_int_array(game->screen_buffer, game->screen_height);
    game->screen_buffer = malloc(sizeof(int*) * (game->screen_height - 1));
    i = 0;
    while (i < game->screen_height)
    {
        game->screen_buffer[i] = malloc(sizeof(int) * (game->screen_width - 1));
        i++;
    }
}

int init_textures(t_game *game)
{
    char *texture_paths[4] = { "./assets/eagle.xpm", "./assets/eagle.xpm", "./assets/purplestone.xpm", "./assets/purplestone.xpm"};
    int i;
    int width;
    int height;

	width = game->tex_size;
	height = game->tex_size;
    i = 0;
    while (i < 4)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx, texture_paths[i], &width, &height);
        if (!game->textures[i].img)
            return (0);
        game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img, &game->textures[i].bits_per_pixel,
			&game->textures[i].size_line, &game->textures[i].endian);
        if (!game->textures[i].addr)
            return (0);
        game->textures[i].width = width;
        game->textures[i].height = height;
        i++;
    }
    return (1);
}

t_game	*init_game(t_map_info map_info)
{
	t_game		*game;

	game = malloc(sizeof(t_game));
	game->screen_buffer = NULL;
	game->map_info = map_info;
	game->screen_height = 600;
	game->screen_width = 800;
	game->tex_size = 64;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->screen_width, game->screen_height, "Cub3d");
	game->player_pos_x = map_info.player_x;
	game->player_pos_y = map_info.player_y;
	game->player_dir_x = -1;
	game->player_dir_y = 0;
	game->plane_x = 0;
	game->plane_y = -0.66;
	game->player_move_x = 0;
	game->player_move_y = 0;
	init_textures(game);
	init_screen_buffer(game);
	return (game);
}