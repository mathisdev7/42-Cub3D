/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:34:43 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 10:46:15 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map_info	*set_cardinals_path(char *line, t_map_info *map_info)
{
	if (line[0] == 'N')
		map_info->no_path = ft_strdup(line + 3);
	else if (line[0] == 'S')
		map_info->so_path = ft_strdup(line + 3);
	else if (line[0] == 'E')
		map_info->ea_path = ft_strdup(line + 3);
	else if (line[0] == 'W')
		map_info->we_path = ft_strdup(line + 3);
	free(line);
	return (map_info);
}
