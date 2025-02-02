/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:51:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 15:55:25 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_parse_data(t_parse_data *data, char *map_path)
{
	data->map_path = map_path;
	data->map = allocate_map_array(data->map_path, &data->count);
	if (!data->map)
		return (1);
	data->fd = open(data->map_path, O_RDONLY);
	if (data->fd < 0)
		return (1);
	data->line = remove_spaces(get_next_line(data->fd));
	data->max_len = 0;
	data->k = 0;
	return (0);
}

void	cleanup_parse_data(t_parse_data *data)
{
	int	i;

	if (data->map)
	{
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	free(data->line);
	close(data->fd);
}
