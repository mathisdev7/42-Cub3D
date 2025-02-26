/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:58:59 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 16:52:21 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	init_xpm_texture(t_game *game, char *filename)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(game->mlx, filename, &texture.width,
			&texture.height);
	texture.addr = (int *)mlx_get_data_addr(texture.img,
			&texture.bits_per_pixel, &texture.size_line, &texture.endian);
	return (texture);
}

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
