/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:31 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 15:30:39 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_asset_line(char *line, t_map_info *map_info)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		map_info->no_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO", 2) == 0)
		map_info->so_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE", 2) == 0)
		map_info->we_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA", 2) == 0)
		map_info->ea_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F", 1) == 0)
		map_info->floor_color = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C", 1) == 0)
		map_info->ceiling_color = ft_strdup(line + 2);
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
	while (raw_line)
	{
		processed_line = remove_spaces(raw_line);
		free(raw_line);
		if (processed_line)
		{
			process_asset_line(processed_line, map_info);
			free(processed_line);
		}
		raw_line = get_next_line(fd);
	}
	close(fd);
	return (map_info);
}
