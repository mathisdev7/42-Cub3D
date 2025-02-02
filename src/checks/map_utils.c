/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:53:24 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 10:56:44 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	get_map_size(char *map_path)
{
	int		fd;
	char	*line;
	size_t	count;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), 1);
	line = get_next_line(fd);
	while (line[0] != '1')
	{
		free(line);
		line = get_next_line(fd);
	}
	count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

char	**allocate_map_array(char *map_path, int *count)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	*count = 0;
	line = get_next_line(fd);
	while (line)
	{
		(*count)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map = malloc(sizeof(char *) * (*count + 1));
	if (!map)
		return (NULL);
	return (map);
}
