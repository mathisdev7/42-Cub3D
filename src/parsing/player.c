/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:57:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/09 00:40:03 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_direction(char player_char, t_map_info *map_info)
{
	const t_direction	directions[] = {{'N', 0, -1}, {'S', 0, 1}, {'E', 1, 0},
	{'W', -1, 0}};
	int					i;

	i = -1;
	while (++i < 4)
	{
		if (directions[i].dir == player_char)
		{
			map_info->player_dir_x = directions[i].x;
			map_info->player_dir_y = directions[i].y;
			map_info->player_plane_x = -map_info->player_dir_y * 0.66;
			map_info->player_plane_y = map_info->player_dir_x * 0.66;
			return ;
		}
	}
}

static char	get_player_char(char c)
{
	char	*valid_chars;
	char	*ptr;

	valid_chars = "NSEW";
	ptr = ft_strchr(valid_chars, c);
	if (ptr)
		return (*ptr);
	return (0);
}

static int	process_map_row(char *row, t_map_info *map_info)
{
	int		j;
	char	player_char;

	j = -1;
	while (row[++j])
	{
		player_char = get_player_char(row[j]);
		if (player_char)
		{
			set_player_direction(player_char, map_info);
			return (0);
		}
	}
	return (1);
}

int	check_map_player(char **map, t_map_info *map_info)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (process_map_row(map[i], map_info) == 0)
			return (0);
	}
	return (1);
}
