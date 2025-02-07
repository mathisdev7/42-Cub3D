/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:12:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/06 21:19:41 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**allocate_map_copy(size_t map_len)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (map_len + 1));
	if (!copy)
		return (NULL);
	return (copy);
}

static char	*process_line(const char *src_line)
{
	char	*dest_line;
	size_t	j;
	size_t	k;

	dest_line = malloc(ft_strlen(src_line) + 1);
	if (!dest_line)
		return (NULL);
	j = 0;
	k = 0;
	while (src_line[j])
	{
		if (src_line[j] == ' ' || src_line[j] == '\t' || src_line[j] == '\n')
			j++;
		else
			dest_line[k++] = src_line[j++];
	}
	dest_line[k] = '\0';
	return (dest_line);
}

char	**copy_map(char **map)
{
	size_t	i;
	char	**map_copy;
	size_t	map_len;

	map_len = ft_array_len(map);
	map_copy = allocate_map_copy(map_len);
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < map_len)
	{
		map_copy[i] = process_line(map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
