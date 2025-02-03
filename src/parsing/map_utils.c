/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:53:24 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 09:28:22 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*find_first_map_line(int fd)
{
	char	*line;

	line = remove_map_spaces(get_next_line(fd));
	if (!line)
		return (NULL);
	while (line && line[0] != '1')
	{
		free(line);
		line = remove_map_spaces(get_next_line(fd));
	}
	return (line);
}

static size_t	count_remaining_lines(int fd, char *first_line)
{
	size_t	count;
	char	*temp;
	char	*line;

	count = 1;
	free(first_line);
	line = get_next_line(fd);
	while (line)
	{
		temp = line;
		line = remove_map_spaces(line);
		free(temp);
		count++;
		line = get_next_line(fd);
	}
	return (count);
}

size_t	get_map_size(char *map_path)
{
	int		fd;
	char	*first_line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), 1);
	first_line = find_first_map_line(fd);
	if (!first_line)
		return (close(fd), 1);
	close(fd);
	return (count_remaining_lines(fd, first_line));
}

char	**allocate_map_array(char *map_path)
{
	char	**map;

	map = malloc(sizeof(char *) * (get_map_size(map_path) + 1));
	if (!map)
		return (NULL);
	return (map);
}

void	pad_map_lines(char **map, int max_len)
{
	int	k;

	k = 0;
	while (map[k])
	{
		map[k] = ft_strpad(map[k], max_len, ' ');
		k++;
	}
}
