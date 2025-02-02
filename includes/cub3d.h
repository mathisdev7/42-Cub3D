/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 10:56:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Structure definitions will go here

// Function prototypes will go here
int		check_args(int argc, char **argv);
int		check_map(char *map_path);
int		check_cardinal_points(char *line);
int		check_file(char *arg);
char	*remove_spaces(char *line);
void	ft_free_array(char **array);
int		check_map_content(char **map);
char	**parse_map(char *map_path);
size_t	get_map_size(char *map_path);
char	**allocate_map_array(char *map_path, int *count);

#endif
