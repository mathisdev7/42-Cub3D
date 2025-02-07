/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:09:45 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 19:53:13 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_check_map_data(t_check_map_data *data, char *map_path)
{
	data->i = 0;
	data->fd = open(map_path, O_RDONLY);
	if (data->fd == -1)
		return (1);
	if (get_map_size(map_path) == 0)
		return (1);
	data->map = malloc(sizeof(char *) * (get_map_size(map_path) + 1));
	if (!data->map)
	{
		close(data->fd);
		return (1);
	}
	data->line = get_next_line(data->fd);
	if (!data->line)
	{
		close(data->fd);
		free(data->map);
		return (1);
	}
	return (0);
}

static void	cleanup_check_map_data(t_check_map_data *data)
{
	if (data->line)
		free(data->line);
	if (data->temp)
		free(data->temp);
	if (data->cleaned)
		free(data->cleaned);
	close(data->fd);
	data->map[data->i] = NULL;
}

static int	process_line(t_check_map_data *data)
{
	data->temp = remove_n(data->line);
	if (!data->temp)
		return (1);
	data->cleaned = remove_spaces(data->line);
	if (!data->cleaned)
	{
		free(data->temp);
		return (1);
	}
	if (data->cleaned[0] == '1' || data->cleaned[0] == '0')
	{
		data->map[data->i++] = ft_strdup(data->temp);
		if ((int)ft_strlen(data->temp) > data->max_len)
			data->max_len = ft_strlen(data->temp);
	}
	free(data->temp);
	free(data->cleaned);
	free(data->line);
	data->temp = NULL;
	data->cleaned = NULL;
	data->line = NULL;
	return (0);
}

char	**check_map(char *map_path)
{
	t_check_map_data	data;

	ft_memset(&data, 0, sizeof(t_check_map_data));
	if (init_check_map_data(&data, map_path))
		return (NULL);
	while (data.line)
	{
		if (process_line(&data))
		{
			cleanup_check_map_data(&data);
			if (data.map)
				free_map(data.map);
			return (NULL);
		}
		data.line = get_next_line(data.fd);
	}
	if (data.i == 0)
	{
		cleanup_check_map_data(&data);
		if (data.map)
			free_map(data.map);
		return (NULL);
	}
	cleanup_check_map_data(&data);
	return (data.map);
}
