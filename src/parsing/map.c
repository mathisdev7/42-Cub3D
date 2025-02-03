/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:09:45 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 14:10:56 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*init_map_parsing(char *map_path, int *fd)
{
	char	*line;
	char	*cleaned;

	cleaned = NULL;
	*fd = open(map_path, O_RDONLY);
	if (*fd < 0)
		return (NULL);
	line = get_next_line(*fd);
	cleaned = remove_spaces(line);
	while (cleaned && cleaned[0] != '1')
	{
		free(line);
		free(cleaned);
		line = get_next_line(*fd);
		cleaned = remove_spaces(line);
	}
	free(cleaned);
	return (line);
}

static void	parse_map_lines(int fd, char **map, char *line)
{
	int	i;

	i = 0;
	while (line)
	{
		map[i] = remove_n(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
}

char	**parse_all_map(char *map_path)
{
	size_t	map_size;
	char	**map;
	int		fd;
	char	*line;

	map_size = get_map_size(map_path);
	map = malloc(sizeof(char *) * (map_size + 1));
	if (!map)
		return (NULL);
	line = init_map_parsing(map_path, &fd);
	if (!line)
		return (free(map), close(fd), NULL);
	parse_map_lines(fd, map, line);
	close(fd);
	return (map);
}

static int	validate_map_file(int *fd, char **line, char *map_path)
{
	char	*cleaned;
	int		count;

	cleaned = NULL;
	*fd = open(map_path, O_RDONLY);
	if (*fd == -1)
		return (1);
	*line = get_next_line(*fd);
	if (*line == NULL)
		return (close(*fd), 1);
	count = 0;
	if (read_lines(*fd, &count, *line, cleaned) != 0)
		return (close(*fd), gnl_cleanup(*fd), 1);
	return (0);
}

char	**check_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**map;
	char	**new_map;

	if (validate_map_file(&fd, &line, map_path))
		return (NULL);
	map = parse_map(map_path);
	if (map == NULL)
		return (close(fd), gnl_cleanup(fd), NULL);
	if (check_map_content(map) != 0)
		return (close(fd), gnl_cleanup(fd), ft_free_array(map), NULL);
	new_map = parse_all_map(map_path);
	ft_free_array(map);
	map = new_map;
	gnl_cleanup(fd);
	close(fd);
	return (map);
}
