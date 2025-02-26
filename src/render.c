/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:53:00 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 17:24:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_screen(t_game *game)
{
	int			x;
	int			y;
	t_texture	screen_texture;

	y = 0;
	screen_texture.img = NULL;
	screen_texture.img = mlx_new_image(game->mlx, game->screen_width,
			game->screen_height);
	screen_texture.addr = (int *)mlx_get_data_addr(screen_texture.img,
			&screen_texture.bits_per_pixel, &screen_texture.size_line,
			&screen_texture.endian);
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			set_pixel_color(game, x, y, &screen_texture);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, screen_texture.img, 0, 0);
	mlx_destroy_image(game->mlx, screen_texture.img);
}

void	clear_screen_buffer(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			game->screen_buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	move_player(game);
	clear_screen_buffer(game);
	init_raycast(&game->raycast);
	raycasting(&game->raycast, game);
	fill_screen(game);
	return (0);
}

int	close_game(t_game *game)
{
	int	i;

	i = 0;
	free_int_array(game->screen_buffer, game->screen_height);
	while (i < 4)
	{
		mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	render_game(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press_handler, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release_handler, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
}
