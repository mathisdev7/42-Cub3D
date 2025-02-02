/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:48:54 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 12:51:33 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**parse_map(char *map_path)
{
	t_parse_data	data;

	ft_memset(&data, 0, sizeof(t_parse_data));
	if (init_parse_data(&data, map_path))
		return (cleanup_parse_data(&data), NULL);
	if (skip_non_map_lines(data.fd, &data.line))
		return (cleanup_parse_data(&data), NULL);
	if (process_map_lines(data.fd, data.map, data.line))
		return (cleanup_parse_data(&data), NULL);
	close(data.fd);
	data.k = -1;
	while (data.map[++data.k])
	{
		if ((int)ft_strlen(data.map[data.k]) > data.max_len)
			data.max_len = ft_strlen(data.map[data.k]);
	}
	pad_map_lines(data.map, data.max_len);
	return (data.map);
}

static int	validate_map_borders(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if ((i == 0 || i == height - 1 || j == 0 || j == width - 1)
				&& map[i][j] != '1' && map[i][j] != ' ')
				return (1);
			if (map[i][j] == '0' && (i == 0 || i == height - 1 || j == 0
					|| j == width - 1))
				return (1);
		}
	}
	return (0);
}

static int	validate_player_position(char **map, int height, int width)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				player_count++;
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
					return (1);
			}
		}
	}
	return (player_count != 1);
}

static int	validate_map_characters(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (!ft_strchr(" 01NSEW", map[i][j]))
				return (1);
		}
	}
	return (0);
}

int	check_map_content(char **map)
{
	int	height;
	int	width;
	int	error;

	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	error = 0;
	error += validate_map_borders(map, height, width);
	error += validate_player_position(map, height, width);
	error += validate_map_characters(map, height, width);
	return (error);
}
