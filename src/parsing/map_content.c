/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:48:54 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 07:27:48 by mazeghou         ###   ########.fr       */
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

int	check_map_content(char **map)
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
	return (error);
}
