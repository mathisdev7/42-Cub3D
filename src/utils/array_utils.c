/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:42:19 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 11:23:38 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	get_map_size_2(char **map)
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

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void*)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
