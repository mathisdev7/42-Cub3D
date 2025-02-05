/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:26:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/05 15:42:08 by mazeghou         ###   ########.fr       */
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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
}			t_map_info;

typedef struct s_rectangle_data
{
	size_t	i;
	size_t	j;
	size_t	top;
	size_t	bottom;
}			t_rectangle_data;

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

typedef struct s_check_map_data
{
	int		fd;
	char	*line;
	char	*cleaned;
	char	*temp;
	char	**map;
	int		i;
	int		max_len;
}			t_check_map_data;

#endif
