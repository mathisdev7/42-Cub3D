/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:06:12 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/05 15:48:30 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map_info	*set_color(char *line, t_map_info *map_info)
{
	if (ft_strstr(line, "F"))
		map_info->floor_color = remove_spaces(line + 2);
	else if (ft_strstr(line, "C"))
		map_info->ceiling_color = remove_spaces(line + 2);
	free(line);
	return (map_info);
}

t_map_info	*parse_color(char *line, t_map_info *map_info)
{
	int		fd;
	char	*raw_line;
	char	*processed_line;

	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (close(fd), NULL);
	raw_line = get_next_line(fd);
	while (raw_line != NULL)
	{
		if (ft_strstr(raw_line, "F") || ft_strstr(raw_line, "C"))
		{
			processed_line = remove_spaces(raw_line);
			map_info = set_color(processed_line, map_info);
			free(raw_line);
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
