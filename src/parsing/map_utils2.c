/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:51:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/06 12:59:12 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_map_spaces(char *line)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	if (!line)
		return (free(new_line), NULL);
	while (i < ft_strlen(line))
	{
		if ((i > 0 && line[i] == ' ' && line[i - 1] != '1' && line[i
					- 1] != '0') || line[i] == '\n' || line[i] == '\t'
			|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r'
			|| (line[i] == ' ' && line[i + 1] == ' '))
			i++;
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

int	skip_non_map_lines(int fd, char **line)
{
	char	*cleaned;

	while (*line)
	{
		cleaned = remove_spaces(*line);
		if (cleaned && cleaned[0] == '1')
		{
			free(cleaned);
			return (0);
		}
		free(*line);
		free(cleaned);
		*line = get_next_line(fd);
		if (!*line)
			return (1);
	}
	return (1);
}

int	process_map_lines(int fd, char **map, char *line)
{
	int	i;

	i = 0;
	while (line)
	{
		map[i] = remove_spaces(line);
		free(line);
		if (!map[i])
			return (1);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (0);
}

int	init_parse_data(t_parse_data *data, char *map_path)
{
	data->map_path = map_path;
	data->map = allocate_map_array(data->map_path);
	if (!data->map)
		return (1);
	data->fd = open(data->map_path, O_RDONLY);
	if (data->fd < 0)
		return (1);
	data->line = get_next_line(data->fd);
	data->max_len = 0;
	data->k = 0;
	return (0);
}

void	cleanup_parse_data(t_parse_data *data)
{
	int	i;

	if (data->map)
	{
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	free(data->line);
	close(data->fd);
}
