/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 14:59:17 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	char		**map;
	t_map_info	map_info;

	if (check_args(argc, argv))
		return (printf("error args\n"), 0);
	map = check_map(argv[1]);
	if (map == NULL)
		return (printf("error map\n"), 0);
	map_info = map_to_struct(map, argv[1]);
	printf("map width: %d\n", map_info.map_width);
	printf("map height: %d\n", map_info.map_height);
	printf("player x: %d\n", map_info.player_x);
	printf("player y: %d\n", map_info.player_y);
	printf("player angle: %f\n", map_info.player_angle);
	printf("no path: %s\n", map_info.no_path);
	printf("so path: %s\n", map_info.so_path);
	printf("we path: %s\n", map_info.we_path);
	printf("ea path: %s\n", map_info.ea_path);
	printf("floor color: %s\n", map_info.floor_color);
	printf("ceiling color: %s\n", map_info.ceiling_color);
	free_map(map);
	return (0);
}
