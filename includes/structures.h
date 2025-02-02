/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:26:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 14:55:38 by mazeghou         ###   ########.fr       */
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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
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
