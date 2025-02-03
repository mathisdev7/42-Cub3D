/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:06:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 14:18:19 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_lines(char *line)
{
	if (line[0] == 'C' || line[0] == 'F')
	{
		if (line[1] != ' ')
			return (0);
		if (!is_rgb(line + 2))
			return (0);
		return (1);
	}
	return (0);
}

static int	process_empty_line(int fd, char **line)
{
	char	*raw;
	char	*new_clean;

	free(*line);
	raw = get_next_line(fd);
	if (!raw)
		return (1);
	new_clean = remove_spaces(raw);
	free(raw);
	*line = new_clean;
	return (*line == NULL);
}

static int	validate_line_content(char *line, int *count)
{
	if (line[0] == 'O' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'N')
	{
		(*count)++;
		if (!check_cardinal_points(line))
			return (0);
	}
	else if (line[0] == 'C' || line[0] == 'F')
	{
		if (!check_lines(line))
			return (0);
	}
	return (1);
}

int	read_lines(int fd, int *count, char *line, char *cleaned)
{
	while (line)
	{
		cleaned = remove_spaces(line);
		free(line);
		line = cleaned;
		if (!line)
			return (1);
		if (line[0] == '\0' && process_empty_line(fd, &line))
			return (1);
		if (!validate_line_content(line, count))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
