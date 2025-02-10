/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:01 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/10 16:14:38 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void play_sound(const char *path)
{
    char command[256];
    snprintf(command, sizeof(command), "aplay %s > /dev/null 2>&1 &", path);  // Le `&` permet de lancer en arrière-plan
    system(command);
}

void shoot_weapon(t_game *game)
{
    double bullet_x;
    double bullet_y;
    double steps;
    
    steps = 0.05;
    play_sound("./assets/base/33.wav");
    init_pistol(game, "./assets/base/gun_fire.xpm");
    while (steps < SHOOT_DISTANCE)
    {
        bullet_x = game->player_pos_x + game->player_dir_x * steps;
        bullet_y = game->player_pos_y + game->player_dir_y * steps;

        if (game->map_info.map[(int)bullet_y][(int)bullet_x] == '1')
            break;
        double distance_to_sprite = sqrt(pow(bullet_x - game->sprite.x, 2) + pow(bullet_y - game->sprite.y, 2));
        if (distance_to_sprite < SHOOT_PRECISION)
        {
            init_sprite(game, "./assets/base/dead.xpm");
            break;
        }

        steps += 0.05;
    }
}