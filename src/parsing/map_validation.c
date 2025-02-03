/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:01:55 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 09:57:28 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t get_map_size_2(char **map)
{
	size_t i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

size_t is_map_rectangle(char **map)
{
	size_t i = 0;
	size_t j = 0;
	size_t top = 0;
	size_t bottom = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0)
				top++;
			else if (i == get_map_size_2(map) - 1)
				bottom++;
			j++;
		}
		i++;
	}
	j = ft_strlen(remove_spaces(map[0]));
	i = 1;
	while (map[i])
	{
		if (j != ft_strlen(remove_spaces(map[i])))
			return (1);
		i++;
	}
	if (top != bottom)
		return (1);
	return (0);
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
	if (!is_map_rectangle(map))
	{
		if (!check_map_borders(map))
			return (0);
		return (1);
	}
	else
		return (1);
}
