/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:53:00 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/10 06:28:58 by nopareti         ###   ########.fr       */
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
		set_image_pixel(screen_texture, x, y, 0x808080);
	else if (y < game->screen_height - 1)
		set_image_pixel(screen_texture, x, y, 0x141414);
}

static int	key_press_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z)
		game->player_move_y = 1;
	if (key == XK_q)
		game->player_move_x = -1;
	if (key == XK_s)
		game->player_move_y = -1;
	if (key == XK_d)
		game->player_move_x = 1;
	if (key == XK_Right)
		game->player_rotate = 1;
	if (key == XK_Left)
		game->player_rotate = -1;
	return (0);
}

static int	key_release_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z && game->player_move_y == 1)
		game->player_move_y = 0;
	if (key == XK_s && game->player_move_y == -1)
		game->player_move_y = 0;
	if (key == XK_q && game->player_move_x == -1)
		game->player_move_x += 1;
	if (key == XK_d && game->player_move_x == 1)
		game->player_move_x -= 1;
	if (key == XK_Right && game->player_rotate == 1)
		game->player_rotate = 0;
	if (key == XK_Left && game->player_rotate == -1)
		game->player_rotate = 0;
	return (0);
}

void move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	
    new_x = game->player_pos_x + game->player_dir_x * MOVESPEED;
    new_y = game->player_pos_y + game->player_dir_y * MOVESPEED;

    if (game->map_info.map[(int)game->player_pos_y][(int)new_x] != '1')
        game->player_pos_x = new_x;
    if (game->map_info.map[(int)new_y][(int)game->player_pos_x] != '1')
        game->player_pos_y = new_y;
}


void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos_x - game->player_dir_x * MOVESPEED;
    new_y = game->player_pos_y - game->player_dir_y * MOVESPEED;

	if (game->map_info.map[(int)game->player_pos_y][(int)new_x] != '1')
        game->player_pos_x = new_x;
    if (game->map_info.map[(int)new_y][(int)game->player_pos_x] != '1')
        game->player_pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos_x - game->player_dir_y * MOVESPEED;
    new_y = game->player_pos_y + game->player_dir_x * MOVESPEED;

	if (game->map_info.map[(int)game->player_pos_y][(int)new_x] != '1')
        game->player_pos_x = new_x;
    if (game->map_info.map[(int)new_y][(int)game->player_pos_x] != '1')
        game->player_pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos_x + game->player_dir_y * MOVESPEED;
    new_y = game->player_pos_y - game->player_dir_x * MOVESPEED;
	if (game->map_info.map[(int)game->player_pos_y][(int)new_x] != '1')
        game->player_pos_x = new_x;
    if (game->map_info.map[(int)new_y][(int)game->player_pos_x] != '1')
        game->player_pos_y = new_y;
}

void rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

    old_dir_x = game->player_dir_x;
    game->player_dir_x = game->player_dir_x * cos(ROTSPEED) - game->player_dir_y * sin(ROTSPEED);
    game->player_dir_y = old_dir_x * sin(ROTSPEED) + game->player_dir_y * cos(ROTSPEED);

    old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(ROTSPEED) - game->plane_y * sin(ROTSPEED);
    game->plane_y = old_plane_x * sin(ROTSPEED) + game->plane_y * cos(ROTSPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player_dir_x;
	game->player_dir_x = game->player_dir_x * cos(-ROTSPEED) - game->player_dir_y * sin(-ROTSPEED);
	game->player_dir_y = old_dir_x * sin(-ROTSPEED) + game->player_dir_y * cos(-ROTSPEED);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(-ROTSPEED) - game->plane_y * sin(-ROTSPEED);
	game->plane_y = old_plane_x * sin(-ROTSPEED) + game->plane_y * cos(-ROTSPEED);
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

int	check_collision(t_game *game, char movement_type)
{
	if (movement_type == 'F')
	{
		if (game->map_info.map[(int)game->player_pos_y][(int)game->player_pos_x] == '1')
		{
			return (1);
		}
		return (0);
	}
	return (0);
}

void	move_player(t_game *game)
{
	if (game->player_move_y == 1)
		move_forward(game);
	if (game->player_move_y == -1)
		move_backward(game);
	if (game->player_move_x == 1)
		move_right(game);
	if (game->player_move_x == -1)
		move_left(game);
	if (game->player_rotate == 1)
		rotate_right(game);
	if (game->player_rotate == -1)
		rotate_left(game);
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
