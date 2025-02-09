/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/09 14:18:56 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game_info(t_game *game, t_map_info *map_info, char **map)
{
	game = init_game(*map_info);
	render_game(game);
	free_all(map, map_info);
}

int	main(int argc, char **argv)
{
	char		**map;
	t_map_info	map_info;
	t_game		*game;

	if (check_initial_conditions(argc, argv))
		return (0);
	map = check_map(argv[1]);
	if (check_map_validity(map, argv[1]))
		return (0);
	ft_memset(map_info.tab_assets, 0, 256);
	map_info = map_to_struct(map, argv[1]);
	if (check_assets_validity(&map_info))
		return (free_all(map, &map_info), 0);
	if (check_map_and_colors(map, &map_info, argv[1]))
		return (free_all(map, &map_info), 0);
	game = NULL;
	init_game_info(game, &map_info, map);
	return (0);
}
