/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:06:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 08:06:42 by mazeghou         ###   ########.fr       */
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

int	read_lines(int fd, int *count, char *line, char *cleaned)
{
	while (line)
	{
		cleaned = remove_spaces(line);
		free(line);
		line = cleaned;
		if (!line)
			return (free(line), 1);
		if (line[0] == '\0')
			line = remove_spaces(get_next_line(fd));
		if (line[0] == 'O' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E'
			|| line[0] == 'N')
		{
			(*count)++;
			if (!check_cardinal_points(line))
				return (free(line), 1);
		}
		else if (line[0] == 'C' || line[0] == 'F')
		{
			if (!check_lines(line))
				return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
