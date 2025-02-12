/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:56:31 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/11 15:19:55 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void render_sprites(t_game *game, double *z_buffer)
{
    int num_sprite = 1;
    t_sprite sprite[num_sprite];
    sprite[0].x = game->sprite.x;
    sprite[0].y = game->sprite.y;
    sprite[0].texture = game->sprite.texture;

    //int spriteOrder[num_sprite];
    //double spriteDistance[num_sprite];
    //void sortSprites(int* order, double* dist, int amount);

    /*for (int i = 0; i < num_sprite; i++)
    {
        spriteDistance[i] = ((game->player.pos_x - sprite[i].x) * 
            (game->player.pos_x - sprite[i].x) +
            (game->player.pos_y - sprite[i].y) * (game->player.pos_y - sprite[i].y));
    }*/

    for (int i = 0; i < num_sprite; i++)
    {
        double sprite_x = sprite[i].x - game->player.pos_x;
        double sprite_y = sprite[i].y - game->player.pos_y;

        double invDet = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y); 

        double transformX = invDet * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
        double transformY = invDet * (-game->player.plane_y * sprite_x + game->player.plane_x * sprite_y); 

        int spriteScreenX = (int)(game->screen_width / 2) * (1 + transformX / transformY);

        int spriteHeight = fabs((int)game->screen_height / (transformY));
        int drawStartY = -spriteHeight / 2 + game->screen_height / 2;
        if (drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + game->screen_height / 2;
        if (drawEndY >= game->screen_height) drawEndY = game->screen_height - 1;

        int spriteWidth = fabs((int)game->screen_height / (transformY));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= game->screen_width) drawEndX = game->screen_width - 1;
        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprite->texture.width / spriteWidth) / 256;

            if (transformY > 0 && stripe > 0 && stripe < game->screen_width && transformY < z_buffer[stripe])
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = y * 256 - game->screen_height * 128 + spriteHeight * 128;
                    int texY = ((d * sprite->texture.height) / spriteHeight) / 256;

                    int color = sprite->texture.addr[texY * sprite->texture.width + texX];

                    if ((color & 0x00FFFFFF) != 0) // Ignore transparent pixels
                    {
                        if (y >= 0 && y < game->screen_height && stripe >= 0 && stripe < game->screen_width)
                        {
                            game->screen_buffer[y][stripe] = color;
                        }
                    }
                }
            }
        }
    }
}