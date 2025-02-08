/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:08:37 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/08 11:56:58 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_line_full_of_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	skip_to_map_start(int fd, char **line, char **map)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (map[i] && *line && !ft_strstr(*line, map[i]))
	{
		tmp = *line;
		*line = get_next_line(fd);
		free(tmp);
	}
	return (i);
}

int	check_if_map_last(int fd, char **line, char **map, size_t i)
{
	if (i == get_map_size_2(map))
	{
		free(*line);
		*line = get_next_line(fd);
		if (*line)
			return (1);
	}
	return (0);
}

int	process_map_lines_last(int fd, char **line, char **map, size_t i)
{
	while (map[i] && *line && ft_strstr(*line, map[i]))
	{
		free(*line);
		*line = get_next_line(fd);
		i++;
	}
	if (!*line)
		return (free(*line), 0);
	while (*line && (is_line_full_of_spaces(*line) != 0))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	gnl_cleanup(fd);
	return (0);
}

int	is_map_last(char *map_path, char **map)
{
	int		fd;
	char	*line;
	size_t	i;
	int		result;

	result = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), 0);
	line = get_next_line(fd);
	i = skip_to_map_start(fd, &line, map);
	if (check_if_map_last(fd, &line, map, i))
		result = 1;
	if (result == 0 && process_map_lines_last(fd, &line, map, i))
		result = 1;
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	gnl_cleanup(fd);
	return (close(fd), result);
}
