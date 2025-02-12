/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:56:31 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/12 12:24:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

void	render_sprites(t_game *game, double *z_buffer)
{
	int			num_sprite;
	t_sprite	sprite[1];
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

	num_sprite = 1;
	sprite[0].x = game->sprite.x;
	sprite[0].y = game->sprite.y;
	sprite[0].texture = game->sprite.texture;
	// int spriteOrder[num_sprite];
	// double spriteDistance[num_sprite];
	// void sortSprites(int* order, double* dist, int amount);
	/*for (int i = 0; i < num_sprite; i++)
	{
		spriteDistance[i] = ((game->player_pos_x - sprite[i].x) *
			(game->player_pos_x - sprite[i].x) +
			(game->player_pos_y - sprite[i].y) * (game->player_pos_y
				- sprite[i].y));
	}*/
	for (int i = 0; i < num_sprite; i++)
	{
		sprite_x = sprite[i].x - game->player_pos_x;
		sprite_y = sprite[i].y - game->player_pos_y;
		invDet = 1.0 / (game->plane_x * game->player_dir_y - game->player_dir_x
				* game->plane_y);
		transformX = invDet * (game->player_dir_y * sprite_x
				- game->player_dir_x * sprite_y);
		transformY = invDet * (-game->plane_y * sprite_x + game->plane_x
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
					* sprite->texture.width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < game->screen_width
				&& transformY < z_buffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++)
				{
					d = y * 256 - game->screen_height * 128 + spriteHeight
						* 128;
					texY = ((d * sprite->texture.height) / spriteHeight) / 256;
					color = sprite->texture.addr[texY * sprite->texture.width
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
