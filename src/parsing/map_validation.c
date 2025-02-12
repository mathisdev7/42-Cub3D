/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:01:55 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/11 19:14:06 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	count_border_chars(char **map, t_rectangle_data *data)
{
	data->i = 0;
	while (map[data->i])
	{
		data->j = 0;
		while (map[data->i][data->j])
		{
			if (data->i == 0)
				data->top++;
			else if (data->i == ft_array_len(map) - 1)
				data->bottom++;
			data->j++;
		}
		data->i++;
	}
}

static int	check_rectangle_consistency(char **map, size_t ref_len)
{
	t_rectangle_data	data;
	char				*cleaned;

	ft_memset(&data, 0, sizeof(t_rectangle_data));
	data.i = 1;
	while (map[data.i])
	{
		cleaned = remove_spaces(map[data.i]);
		if (ref_len != ft_strlen(cleaned))
		{
			free(cleaned);
			return (1);
		}
		free(cleaned);
		data.i++;
	}
	return (0);
}

size_t	is_map_rectangle(char **map)
{
	t_rectangle_data	data;
	char				*cleaned;
	size_t				ref_len;

	ft_memset(&data, 0, sizeof(t_rectangle_data));
	count_border_chars(map, &data);
	cleaned = remove_spaces(map[0]);
	ref_len = ft_strlen(cleaned);
	free(cleaned);
	return (check_rectangle_consistency(map, ref_len));
}

static int	check_map_borders(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || i == ft_array_len(map) - 1 || j == 0
				|| j == ft_strlen(map[i]) - 1)
				if (map[i][j] != '1')
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(char **map)
{
	char	**map_copy;
	int		valid;

	valid = 0;
	map_copy = copy_map(map);
	if (!is_map_rectangle(map))
	{
		free_map(map_copy);
		if (!check_map_borders(map))
			return (0);
		return (1);
	}
	else
	{
		valid = check_map_borders(map_copy);
		free_map(map_copy);
		return (valid);
	}
}
