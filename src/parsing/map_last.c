/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:08:37 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:09:01 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:06:32 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:06:32 by mazeghou         ###   ########.fr       */
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

	i = 0;
	while (map[i] && *line && !ft_strstr(*line, map[i]))
		*line = get_next_line(fd);
	return (i);
}

int	check_if_map_last(int fd, char **line, char **map, size_t i)
{
	if (i == get_map_size_2(map))
	{
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
		*line = get_next_line(fd);
		i++;
	}
	if (!*line)
		return (0);
	while (*line && (is_line_full_of_spaces(*line) != 0))
		*line = get_next_line(fd);
	if (*line)
		return (1);
	else
		return (0);
}

int	is_map_last(char *map_path, char **map)
{
	int		fd;
	char	*line;
	size_t	i;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	i = skip_to_map_start(fd, &line, map);
	if (check_if_map_last(fd, &line, map, i))
		return (1);
	if (process_map_lines_last(fd, &line, map, i))
		return (1);
	close(fd);
	return (0);
}
