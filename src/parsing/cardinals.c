/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:36:46 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/06 12:59:24 by mazeghou         ###   ########.fr       */
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
		if ((i > 0 && line[i] == ' ' && line[i - 1] != 'F' && line[i - 1] != 'C'
				&& (ft_strchr("NSEW10FC", line[i + 1]) || ft_strchr(",", line[i
							- 1]))) || line[i] == '\n' || line[i] == '\t'
			|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r'
			|| (line[i] == ' ' && line[i + 1] == ' '))
			i++;
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
