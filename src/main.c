/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:38:26 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_file_empty(char *map_path)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (1);
	free(line);
	close(fd);
	return (0);
}

int	check_color(char *color)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	colors = ft_split(color, ',');
	if (!colors)
		return (0);
	if (ft_array_len(colors) != 3)
		return (ft_free_array(colors), 0);
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (colors[i][j] < '0' || colors[i][j] > '9')
				return (ft_free_array(colors), 0);
			j++;
		}
		i++;
	}
	ft_free_array(colors);
	return (1);
}

void	free_all(char **map, t_map_info *map_info)
{
	free_map(map);
	free(map_info->no_path);
	free(map_info->so_path);
	free(map_info->we_path);
	free(map_info->ea_path);
	free(map_info->floor_color);
	free(map_info->ceiling_color);
}

int	main(int argc, char **argv)
{
	char		**map;
	t_map_info	map_info;
	t_game		*game;

	if (check_args(argc, argv))
		return (printf("error args\n"), 0);
	if (is_file_empty(argv[1]))
		return (printf("error file\n"), 0);
	map = check_map(argv[1]);
	if (map == NULL)
		return (printf("error map\n"), 0);
	map_info = map_to_struct(map, argv[1]);
	if (!map_info.no_path || !map_info.so_path || !map_info.we_path || !map_info.ea_path || !map_info.floor_color || !map_info.ceiling_color)
		return (free_all(map, &map_info), printf("error assets\n"), 0);
	if (ft_strstr(map_info.no_path, ".xpm") == NULL
		|| ft_strstr(map_info.so_path, ".xpm") == NULL
		|| ft_strstr(map_info.we_path, ".xpm") == NULL
		|| ft_strstr(map_info.ea_path, ".xpm") == NULL)
		return (free_all(map, &map_info), printf("error assets\n"), 0);
	if (!file_exists(map_info.no_path) || !file_exists(map_info.so_path)
		|| !file_exists(map_info.we_path) || !file_exists(map_info.ea_path))
		return (printf("error assets\n"), 0);
		return (free_all(map, &map_info), printf("error assets\n"), 0);
	if (check_map_content(map, &map_info, argv[1]))
		return (free_all(map, &map_info), printf("error map content\n"), 0);
	if (!check_color(map_info.floor_color)
		|| !check_color(map_info.ceiling_color))
		return (free_all(map, &map_info), printf("error color\n"), 0);
  game = NULL;
	game = init_game(map_info);
	render_game(game);
	for (size_t i = 0; i < ft_array_len(map); i++)
		printf("'%s'\n", map[i]);
	printf("player dir x: %f\n", map_info.player_dir_x);
	printf("player dir y: %f\n", map_info.player_dir_y);
	printf("player plane x: %f\n", map_info.player_plane_x);
	printf("player plane y: %f\n", map_info.player_plane_y);
	printf("map width: %d\n", map_info.map_width);
	printf("map height: %d\n", map_info.map_height);
	printf("player x: %f\n", map_info.player_x);
	printf("player y: %f\n", map_info.player_y);
	printf("no path: %s\n", map_info.no_path);
	printf("so path: %s\n", map_info.so_path);
	printf("we path: %s\n", map_info.we_path);
	printf("ea path: %s\n", map_info.ea_path);
	printf("floor color: %s\n", map_info.floor_color);
	printf("ceiling color: %s\n", map_info.ceiling_color);
	free_all(map, &map_info);
	return (0);
}
