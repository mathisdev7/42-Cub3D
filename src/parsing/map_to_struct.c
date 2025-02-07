/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:28:40 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 10:48:08 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	*find_player(char **map)
{
	size_t	i;
	size_t	j;
	int		*player;

	player = malloc(sizeof(int) * 2);
	if (!player)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (i == 0 || j == 0 || i == ft_array_len(map) - 1
					|| j >= ft_strlen(map[i]) - 1)
					return (free(player), NULL);
				player[0] = i;
				player[1] = j;
				return (player);
			}
		}
	}
	return (free(player), NULL);
}

size_t	ft_array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	set_map_info(t_map_info *map_info, char **map, int max_width)
{
	int	*player_coords;

	player_coords = find_player(map);
	if (!player_coords)
	{
		map_info->player_x = -1;
		map_info->player_y = -1;
		return ;
	}
	map_info->map = map;
	map_info->map_width = max_width;
	map_info->map_height = ft_array_len(map);
	map_info->player_x = player_coords[0];
	map_info->player_y = player_coords[1];
	free(player_coords);
}

void	set_player_position(t_map_info *map_info, int *player_coords)
{
	map_info->player_x = player_coords[0];
	map_info->player_y = player_coords[1];
	free(player_coords);
}

t_map_info	map_to_struct(char **map, char *map_path)
{
	t_map_info	map_info;
	int			*player_coords;
	int			max_width;
	int			height;

	max_width = 0;
	ft_memset(&map_info, 0, sizeof(t_map_info));
	height = 0;
	while (map[height])
		max_width = fmax(max_width, ft_strlen(map[height++]));
	set_map_info(&map_info, map, max_width);
	player_coords = find_player(map);
	parse_assets(map_path, &map_info);
	parse_color(map_path, &map_info);
	if (player_coords)
		set_player_position(&map_info, player_coords);
	else
	{
		map_info.player_x = -1;
		map_info.player_y = -1;
	}
	return (map_info);
}
