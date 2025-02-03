/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:01:55 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 07:33:08 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	if (check_map_borders(map))
		return (0);
	return (0);
}
