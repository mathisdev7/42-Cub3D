/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:48:54 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:14:09 by mazeghou         ###   ########.fr       */
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

int	check_map_elements(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W'
				|| map[i][j] == ' ')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_map_content(char **map, t_map_info *map_info, char *map_path)
{
	int	height;
	int	width;
	int	error;
	int	i;

	height = 0;
	while (map[height])
		height++;
	width = 0;
	i = -1;
	while (map[++i])
		width = fmax(width, (int)ft_strlen(map[i]));
	error = validate_map(map);
	error += check_map_player(map, map_info);
	error += check_map_elements(map);
	error += is_map_last(map_path, map);
	return (error);
}
