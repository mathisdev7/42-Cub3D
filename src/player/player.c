/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:01 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 16:22:07 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_player	init_player(t_game *game)
{
	t_player	player;

	player.pos_x = game->map_info.player_x + 0.5;
	player.pos_y = game->map_info.player_y + 0.5;
	player.dir_x = game->map_info.player_dir_x;
	player.dir_y = game->map_info.player_dir_y;
	player.plane_x = game->map_info.player_plane_x;
	player.plane_y = game->map_info.player_plane_y;
	player.move_x = 0;
	player.move_y = 0;
	player.rotate = 0;
	return (player);
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
