/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:09:45 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/01 21:13:20 by mazeghou         ###   ########.fr       */
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

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	is_rgb(char *line)
{
	char	**line_splitted;
	int		i;
	int		j;
	char	c;
	int		tab_size;

	line_splitted = ft_split(line, ',');
	tab_size = 0;
	while (line_splitted[tab_size])
		tab_size++;
	if (tab_size != 3)
		return (ft_free_array(line_splitted), 0);
	i = 0;
	j = 0;
	while (line_splitted[i])
	{
		c = line_splitted[i][j];
		if (!ft_isdigit(c))
			return (ft_free_array(line_splitted), 0);
		i++;
		j++;
	}
	ft_free_array(line_splitted);
	return (1);
}

int	check_lines(char *line)
{
	if (line[0] == 'C' || line[0] == 'F')
	{
		if (line[1] != ' ')
			return (0);
		if (!is_rgb(line + 3))
			return (0);
		return (1);
	}
	return (0);
}

int	check_map_content(char *map_path)
{
	int		fd;
	char	*line;
	int		count;
	char	*cleaned;

	count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), 1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), gnl_cleanup(fd), 1);
	while (line)
	{
		cleaned = remove_spaces(line);
		free(line);
		line = cleaned;
		if (!line)
			return (free(line), close(fd), gnl_cleanup(fd), 1);
		if (count < 4)
		{
			count++;
			if (!check_cardinal_points(line))
				return (free(line), close(fd), gnl_cleanup(fd), 1);
		}
		else
		{
			count++;
			if ((count == 5 || count == 6) && !check_lines(line))
				return (free(line), close(fd), gnl_cleanup(fd), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (count != 6)
		return (free(line), gnl_cleanup(fd), close(fd), 1);
	gnl_cleanup(fd);
	close(fd);
	return (0);
}
