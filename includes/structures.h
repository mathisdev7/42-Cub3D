/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:26:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 12:51:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map_info
{
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	double	player_angle;
}			t_map_info;

typedef struct s_parse_data
{
	char	**map;
	char	*line;
	int		fd;
	int		count;
	int		max_len;
	int		k;
	char	*map_path;
}			t_parse_data;

#endif
