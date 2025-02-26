/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:42:07 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/26 16:42:07 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z)
		game->player.move_y = 1;
	if (key == XK_q)
		game->player.move_x = -1;
	if (key == XK_s)
		game->player.move_y = -1;
	if (key == XK_d)
		game->player.move_x = 1;
	if (key == XK_Right)
		game->player.rotate = 1;
	if (key == XK_Left)
		game->player.rotate = -1;
	if (key == XK_Escape)
		close_game(game);
	return (0);
}

int	key_release_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_z && game->player.move_y == 1)
		game->player.move_y = 0;
	if (key == XK_s && game->player.move_y == -1)
		game->player.move_y = 0;
	if (key == XK_q && game->player.move_x == -1)
		game->player.move_x += 1;
	if (key == XK_d && game->player.move_x == 1)
		game->player.move_x -= 1;
	if (key == XK_Right && game->player.rotate == 1)
		game->player.rotate = 0;
	if (key == XK_Left && game->player.rotate == -1)
		game->player.rotate = 0;
	return (0);
}
