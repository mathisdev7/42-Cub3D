/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 13:02:47 by mazeghou         ###   ########.fr       */
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
	map_info = map_to_struct(map);
	printf("map width: %d\n", map_info.map_width);
	printf("map height: %d\n", map_info.map_height);
	printf("player x: %d\n", map_info.player_x);
	printf("player y: %d\n", map_info.player_y);
	printf("player angle: %f\n", map_info.player_angle);
	free_map(map);
	free_map(map_info.map);
	return (0);
}
