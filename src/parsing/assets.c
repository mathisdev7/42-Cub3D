/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:31 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 10:46:06 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*parse_cardinal_line(char *line)
{
	char	*processed_line;

	processed_line = remove_spaces(line);
	free(line);
	return (processed_line);
}

t_map_info	*parse_assets(char *map_path, t_map_info *map_info)
{
	int		fd;
	char	*raw_line;
	char	*processed_line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), NULL);
	raw_line = get_next_line(fd);
	while (raw_line != NULL)
	{
		if (ft_strstr(raw_line, "NO") || ft_strstr(raw_line, "SO")
			|| ft_strstr(raw_line, "WE") || ft_strstr(raw_line, "EA"))
		{
			processed_line = parse_cardinal_line(raw_line);
			map_info = set_cardinals_path(processed_line, map_info);
			raw_line = get_next_line(fd);
		}
		else
		{
			free(raw_line);
			raw_line = get_next_line(fd);
		}
	}
	close(fd);
	return (map_info);
}
