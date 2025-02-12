/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:09:22 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/12 19:00:30 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    move_enemy(t_game *game, int enemy_index)
{
    if (game->enemies[enemy_index].is_dead)
        return ;
    game->enemies[enemy_index].pos_x += 0.01;
    game->sprites[enemy_index].x = game->enemies[enemy_index].pos_x;
}

size_t get_enemy_index(t_game *game, double x, double y)
{
	size_t	i;

	i = 0;
	while (i < game->map_info.ennemy_count)
	{
		if (fabs(game->enemies[i].pos_x - x) < 0.2 && fabs(game->enemies[i].pos_y - y) < 0.2)
			return (i);
        i++;
	}
	return (-1);
}

void    init_enemies(t_game *game)
{
    size_t i;

    i = 0;
    while (i < game->map_info.ennemy_count)
    {
        game->enemies[i].health = 100;
        game->enemies[i].is_dead = 0;
        game->enemies[i].pos_x = game->map_info.enemy_pos[i].pos_x + 0.5;
        game->enemies[i].pos_y = game->map_info.enemy_pos[i].pos_y + 0.5;
        game->enemies[i].sprite.texture = init_xpm_texture(game, ENEMY_IDLE_PATH);
        game->enemies[i].sprite.x = game->enemies[i].pos_x;
        game->enemies[i].sprite.y = game->enemies[i].pos_y;
        game->sprites[i] = game->enemies[i].sprite;
        i++;
    }
}