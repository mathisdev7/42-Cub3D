/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:42:19 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/11 19:14:21 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	ft_array_len(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**ft_arraydup(char **array)
{
	char	**new_array;
	size_t	i;
	size_t	count;

	if (!array)
		return (NULL);
	count = 0;
	while (array[count])
		count++;
	new_array = malloc(sizeof(char *) * (count + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			ft_free_array(new_array);
			return (NULL);
		}
		i++;
	}
	new_array[count] = NULL;
	return (new_array);
}
