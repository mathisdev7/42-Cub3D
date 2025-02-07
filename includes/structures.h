/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:26:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 13:29:04 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef	struct	s_tuple
{
	double	x;
	double	y;
}		t_tuple;

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

typedef struct s_texture {
    void    *img;
    int     *addr;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
    int     width;
    int     height;
}			t_texture;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	double	wall_x;
	int 	step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start_y;
	int		draw_end_y;
	int		tex_x;
}			t_raycast;

typedef	struct	s_game
{
	void		*mlx;
	void		*win;
	int			screen_height;
	int			screen_width;
	int			tex_size;
	t_texture	textures[4];
	int			**screen_buffer;
	double		player_pos_x;
	double		player_pos_y;
	double		player_dir_x;
	double		player_dir_y;
	double		plane_x;
	double		plane_y;
	int			player_move_x;
	int			player_move_y;
	t_map_info	map_info;
	t_raycast	raycast;
}			t_game;

#endif
