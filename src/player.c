/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:01 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/12 18:04:05 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_player    init_player(t_game *game)
{
    t_player    player;

    player.pos_x = game->map_info.player_x + 0.5;
    player.pos_y = game->map_info.player_y + 0.5;
    player.dir_x = game->map_info.player_dir_x;
    player.dir_y = game->map_info.player_dir_y;
    player.plane_x = game->map_info.player_plane_x;
    player.plane_y = game->map_info.player_plane_y;
    player.move_x = 0;
    player.move_y = 0;
    player.rotate = 0;
    player.health = 100;
    player.gun_texture = init_xpm_texture(game, GUN_IDLE_PATH);
    return (player);
}

void move_forward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;
	
    new_x = player->pos_x + player->dir_x * MOVESPEED;
    new_y = player->pos_y + player->dir_y* MOVESPEED;

    if (map[(int)player->pos_y][(int)new_x] != '1')
        player->pos_x = new_x;
    if (map[(int)new_y][(int)player->pos_x] != '1')
        player->pos_y = new_y;
}


void    move_backward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVESPEED;
    new_y = player->pos_y - player->dir_y * MOVESPEED;

	if (map[(int)player->pos_y][(int)new_x] != '1')
        player->pos_x = new_x;
    if (map[(int)new_y][(int)player->pos_x] != '1')
        player->pos_y = new_y;
}

void    move_right(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_y * MOVESPEED;
    new_y = player->pos_y + player->dir_x * MOVESPEED;

	if (map[(int)player->pos_y][(int)new_x] != '1')
        player->pos_x = new_x;
    if (map[(int)new_y][(int)player->pos_x] != '1')
        player->pos_y = new_y;
}

void    move_left(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_y * MOVESPEED;
    new_y = player->pos_y - player->dir_x * MOVESPEED;
	if (map[(int)player->pos_y][(int)new_x] != '1')
        player->pos_x = new_x;
    if (map[(int)new_y][(int)player->pos_x] != '1')
        player->pos_y = new_y;
}

void rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(ROTSPEED) - player->dir_y * sin(ROTSPEED);
    player->dir_y = old_dir_x * sin(ROTSPEED) + player->dir_y * cos(ROTSPEED);

    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(ROTSPEED) - player->plane_y * sin(ROTSPEED);
    player->plane_y = old_plane_x * sin(ROTSPEED) + player->plane_y * cos(ROTSPEED);
}

void rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(-ROTSPEED) - player->dir_y * sin(-ROTSPEED);
    player->dir_y = old_dir_x * sin(-ROTSPEED) + player->dir_y * cos(-ROTSPEED);

    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(-ROTSPEED) - player->plane_y * sin(-ROTSPEED);
    player->plane_y = old_plane_x * sin(-ROTSPEED) + player->plane_y * cos(-ROTSPEED);
}

void	move_player(t_game *game)
{
	if (game->player.move_y == 1)
		move_forward(&game->player, game->map_info.map);
	if (game->player.move_y == -1)
		move_backward(&game->player, game->map_info.map);
	if (game->player.move_x == 1)
		move_right(&game->player, game->map_info.map);
	if (game->player.move_x == -1)
		move_left(&game->player, game->map_info.map);
	if (game->player.rotate == 1)
		rotate_right(&game->player);
	if (game->player.rotate == -1)
		rotate_left(&game->player);
}

void shoot_weapon(t_game *game)
{
    double bullet_x;
    double bullet_y;
    double steps;
    double  enemy_dist;
    int     enemy_index;
    
    steps = 0.05;
    play_sound(FIRE_SOUND_PATH);
    game->player.gun_texture = init_xpm_texture(game, GUN_FIRE_PATH);
    while (steps < SHOOT_DISTANCE)
    {
        bullet_x = game->player.pos_x + game->player.dir_x * steps;
        bullet_y = game->player.pos_y + game->player.dir_y * steps;

        if (game->map_info.map[(int)bullet_y][(int)bullet_x] == '1')
            break;
        enemy_index = get_enemy_index(game, bullet_x, bullet_y);
        if (enemy_index != -1)
        {
            enemy_dist = sqrt(pow(bullet_x - game->enemies[enemy_index].pos_x , 2) + pow(bullet_y - game->enemies[enemy_index].pos_y, 2));
            if (enemy_dist < SHOOT_PRECISION && !game->enemies[enemy_index].is_dead)
            {
                game->sprites[enemy_index].texture = init_xpm_texture(game, ENEMY_DEAD_PATH);
                game->enemies[enemy_index].is_dead = 1;
                break;
            }
        }
        steps += 0.05;
    }
}