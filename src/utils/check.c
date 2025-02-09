/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:16:14 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/09 14:18:40 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_initial_conditions(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (printf("error args\n"), 1);
	if (is_file_empty(argv[1]))
		return (printf("error file\n"), 1);
	return (0);
}

int	check_map_validity(char **map, char *map_path)
{
	if (map == NULL)
		return (printf("error map\n"), 1);
	if (map_path == NULL)
		return (printf("error map path\n"), 1);
	return (0);
}

int	check_assets_validity(t_map_info *map_info)
{
	if (!map_info->no_path || !map_info->so_path || !map_info->we_path
		|| !map_info->ea_path || !map_info->floor_color
		|| !map_info->ceiling_color)
		return (printf("error assets\n"), 1);
	if (ft_strstr(map_info->no_path, ".xpm") == NULL
		|| ft_strstr(map_info->so_path, ".xpm") == NULL
		|| ft_strstr(map_info->we_path, ".xpm") == NULL
		|| ft_strstr(map_info->ea_path, ".xpm") == NULL)
		return (printf("error assets\n"), 1);
	if (!file_exists(map_info->no_path) || !file_exists(map_info->so_path)
		|| !file_exists(map_info->we_path) || !file_exists(map_info->ea_path))
		return (printf("error assets\n"), 1);
	return (0);
}

int	check_map_and_colors(char **map, t_map_info *map_info, char *map_path)
{
	if (check_map_content(map, map_info, map_path))
		return (printf("error map content\n"), 1);
	if (!check_color(map_info->floor_color)
		|| !check_color(map_info->ceiling_color))
		return (printf("error color\n"), 1);
	return (0);
}
