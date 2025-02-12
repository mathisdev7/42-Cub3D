/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:56:31 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/12 18:40:35 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_sprites(t_game *game, double *z_buffer)
{
	double		sprite_x;
	double		sprite_y;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawEndY;
	int			spriteWidth;
	int			drawStartX;
	int			drawEndX;
	int			texX;
	int			d;
	int			texY;
	int			color;
	int		order[200];
	double	distance[200];
	int		sprite_index;
	
	for (int i = 0; i < 200; i++)
	{
		double dx = game->sprites[i].x - game->player.pos_x;
		double dy = game->sprites[i].y - game->player.pos_y;
		distance[i] = dx * dx + dy * dy; // Distance au carré (évite sqrt)
		order[i] = i;
	}

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 199 - i; j++)
		{
			if (distance[order[j]] < distance[order[j + 1]])
			{
				int tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
		}
	}
	sprite_index = 0;
	for (int i = 0; i < 200; i++)
	{
		sprite_index = order[i];
		sprite_x = game->sprites[sprite_index].x - game->player.pos_x;
		sprite_y = game->sprites[sprite_index].y - game->player.pos_y;
		invDet = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x
				* game->player.plane_y);
		transformX = invDet * (game->player.dir_y * sprite_x
				- game->player.dir_x * sprite_y);
		transformY = invDet * (-game->player.plane_y * sprite_x + game->player.plane_x
				* sprite_y);
		spriteScreenX = (int)(game->screen_width / 2) * (1 + transformX
				/ transformY);
		spriteHeight = fabs((int)game->screen_height / (transformY));
		drawStartY = -spriteHeight / 2 + game->screen_height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + game->screen_height / 2;
		if (drawEndY >= game->screen_height)
			drawEndY = game->screen_height - 1;
		spriteWidth = fabs((int)game->screen_height / (transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= game->screen_width)
			drawEndX = game->screen_width - 1;
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
					* game->sprites[sprite_index].texture.width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < game->screen_width
				&& transformY < z_buffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++)
				{
					d = y * 256 - game->screen_height * 128 + spriteHeight
						* 128;
					texY = ((d * game->sprites[sprite_index].texture.height) / spriteHeight) / 256;
					color = game->sprites[sprite_index].texture.addr[texY * game->sprites[sprite_index].texture.width
						+ texX];
					if ((color & 0x00FFFFFF) != 0) // Ignore transparent pixels
					{
						if (y >= 0 && y < game->screen_height && stripe >= 0
							&& stripe < game->screen_width)
						{
							game->screen_buffer[y][stripe] = color;
						}
					}
				}
			}
		}
	}
}
