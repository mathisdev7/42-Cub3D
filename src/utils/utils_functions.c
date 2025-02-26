/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:58:59 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:12 by mazeghou         ###   ########.fr       */
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

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

uint32_t	convert_to_hex(const char *input)
{
	t_rgb	rgb;

	rgb.colors = ft_split(input, ',');
	if (!rgb.colors)
		return (0);
	rgb.r = ft_atoi(rgb.colors[0]);
	rgb.g = ft_atoi(rgb.colors[1]);
	rgb.b = ft_atoi(rgb.colors[2]);
	rgb.hex_value = rgb_to_hex(rgb.r, rgb.g, rgb.b);
	ft_free_array(rgb.colors);
	return (rgb.hex_value);
}

void	set_pixel_color(t_game *game, int x, int y, t_texture *screen_texture)
{
	if (game->screen_buffer[y][x] > 0)
		set_image_pixel(screen_texture, x, y, game->screen_buffer[y][x]);
	else if (y < game->screen_height / 2)
		set_image_pixel(screen_texture, x, y,
			convert_to_hex(game->map_info.ceiling_color));
	else if (y < game->screen_height - 1)
		set_image_pixel(screen_texture, x, y,
			convert_to_hex(game->map_info.floor_color));
}
