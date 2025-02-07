/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:53:15 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 12:23:33 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void free_int_array(int **array, int size)
{
    int i;
    
    if (!array)
        return;
    
    i = 0;
    while (i < size)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}
