/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/06 21:15:28 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "structures.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int			check_args(int argc, char **argv);
char		**check_map(char *map_path);
int			check_file(char *arg);
char		*remove_spaces(char *line);
void		ft_free_array(char **array);
int			check_map_content(char **map);
char		**parse_map(char *map_path);
size_t		get_map_size(char *map_path);
char		**allocate_map_array(char *map_path);
int			*find_player(char **map);
char		*remove_n(char *line);
size_t		ft_array_len(char **array);
int			validate_map(char **map);
t_map_info	map_to_struct(char **map, char *map_path);
char		*ft_strpad(char *str, int len, char pad);
int			skip_non_map_lines(int fd, char **line);
int			process_map_lines(int fd, char **map, char *line);
void		pad_map_lines(char **map, int max_len);
int			init_parse_data(t_parse_data *data, char *map_path);
void		cleanup_parse_data(t_parse_data *data);
void		free_map(char **map);
int			is_rgb(char *line);
int			skip_non_map_lines(int fd, char **line);
int			process_map_lines(int fd, char **map, char *line);
char		*remove_map_spaces(char *line);
char		**ft_arraydup(char **array);
t_map_info	*parse_assets(char *map_path, t_map_info *map_info);
size_t		get_map_size_2(char **map);
t_map_info	*set_cardinals_path(char *line, t_map_info *map_info);
t_map_info	*parse_color(char *line, t_map_info *map_info);
int			file_exists(char *path);
char		*ft_strstr(char *str, char *to_find);
int			check_map_borders_not_rectangular(char **map);
char		**copy_map(char **map);

#endif
