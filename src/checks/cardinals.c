/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:36:46 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/01 01:51:58 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_spaces(char *line)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (i < ft_strlen(line))
	{
		if (line[i] == '\n' || line[i] == '\t' || line[i] == '\v'
			|| line[i] == '\f' || line[i] == '\r')
			i++;
		new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

int	check_cardinal_points(char *line)
{
	char	*path;

	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		if (line[2] != ' ')
			return (0);
		path = ft_strdup(line + 3);
		if (!path)
			return (0);
		path = remove_spaces(path);
		if (!path)
			return (0);
		if (access(path, F_OK) == -1)
		{
			free(path);
			return (0);
		}
		free(path);
	}
	return (1);
}
