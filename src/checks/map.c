/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:09:45 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/01 01:52:04 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map(char *map_path)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_map_content(char *map_path)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), 1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 1);
	while (line)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E'
			|| line[0] == 'W')
		{
			if (!check_cardinal_points(line))
			{
				free(line);
				return (close(fd), 1);
			}
			count++;
		}
		else
		{
			free(line);
			return (close(fd), 1);
		}
		line = get_next_line(fd);
	}
	if (count != 4)
		return (close(fd), 1);
	close(fd);
	return (0);
}
