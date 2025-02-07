/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:30:41 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	char		**map;
	t_map_info	map_info;
	t_game		*game;

	if (check_args(argc, argv))
		return (printf("error args\n"), 0);
	map = check_map(argv[1]);
	if (map == NULL)
		return (printf("error map\n"), 0);
	map_info = map_to_struct(map, argv[1]);
	if (!file_exists(map_info.no_path) || !file_exists(map_info.so_path)
		|| !file_exists(map_info.we_path) || !file_exists(map_info.ea_path))
		return (printf("error assets\n"), 0);
	game = NULL;
	game = init_game(map_info);
	render_game(game);
	free_map(map);
	free(map_info.no_path);
	free(map_info.so_path);
	free(map_info.we_path);
	free(map_info.ea_path);
	free(map_info.floor_color);
	free(map_info.ceiling_color);
	free(game->screen_buffer);
	free(game);
	return (0);
}
