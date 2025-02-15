/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:53:00 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/15 22:54:38 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_image_pixel(t_texture *screen_tex, int x, int y, int color)
{
	int	pixel;

	pixel = y * (screen_tex->size_line / 4) + x;
	screen_tex->addr[pixel] = color;
}

void	set_pixel_color(t_game *game, int x, int y, t_texture *screen_texture)
{
	if (game->screen_buffer[y][x] > 0)
		set_image_pixel(screen_texture, x, y, game->screen_buffer[y][x]);
	else if (y < game->screen_height / 2)
		set_image_pixel(screen_texture, x, y, 0xCAAA47);
	else if (y < game->screen_height - 1)
		set_image_pixel(screen_texture, x, y, 0x6C5920);
}

static int	key_press_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z)
		game->player.move_y = 1;
	if (key == XK_q)
		game->player.move_x = -1;
	if (key == XK_s)
		game->player.move_y = -1;
	if (key == XK_d)
		game->player.move_x = 1;
	if (key == XK_Right)
		game->player.rotate = 1;
	if (key == XK_Left)
		game->player.rotate = -1;
	if (key == XK_Control_L)
		shoot_weapon(game);
	return (0);
}

static int	key_release_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z && game->player.move_y == 1)
		game->player.move_y = 0;
	if (key == XK_s && game->player.move_y == -1)
		game->player.move_y = 0;
	if (key == XK_q && game->player.move_x == -1)
		game->player.move_x += 1;
	if (key == XK_d && game->player.move_x == 1)
		game->player.move_x -= 1;
	if (key == XK_Right && game->player.rotate == 1)
		game->player.rotate = 0;
	if (key == XK_Left && game->player.rotate == -1)
		game->player.rotate = 0;
	if (key == XK_Control_L)
		game->player.gun_texture = init_xpm_texture(game, GUN_IDLE_PATH);
	return (0);
}

void    draw_minimap(t_game *game, double scale)
{
    int            j, i;
    int            draw_start_x, draw_start_y;
	t_texture	wall_tex;
	t_texture	floor_tex;
	t_texture 	player_tex;

    wall_tex = init_xpm_texture(game, "./assets/base/wall.xpm");
	floor_tex = init_xpm_texture(game, "./assets/base/floor.xpm");
	player_tex = init_xpm_texture(game, "./assets/base/player_point.xpm");
    double         tile_size = wall_tex.height * scale;

	draw_start_y = 5;
    for (j = 0; game->map_info.map[j]; j++)
    {
        draw_start_x = 5;
        for (i = 0; game->map_info.map[j][i]; i++)
        {
            if (game->map_info.map[j][i] == '1')
                draw_texture_on_screen(game, wall_tex, scale, draw_start_x, draw_start_y);
            else
                draw_texture_on_screen(game, floor_tex, scale, draw_start_x, draw_start_y);
            draw_start_x += tile_size;
        }
        draw_start_y += tile_size;
    }
    double player_minimap_x = game->player.pos_x * tile_size - (player_tex.width * scale * 0.7) / 2;
    double player_minimap_y = game->player.pos_y * tile_size - (player_tex.height * scale * 0.7) / 2;
    draw_texture_on_screen(game, player_tex, scale * 0.7, player_minimap_x + 5, player_minimap_y + 5);
}

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
	int x, y;
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

int	update(void *param) // function called every frame
{
	t_game *game;

	game = (t_game *)param;
	move_player(game);
	clear_screen_buffer(game);
	init_raycast(&game->raycast);
	raycasting(&game->raycast, game);
	draw_texture_on_screen(game, game->player.gun_texture, 6, 100, 100);
	draw_minimap(game, 0.2);
	fill_screen(game);
	return (0);
}

void	render_game(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press_handler, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release_handler, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
}
