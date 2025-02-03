/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:45:39 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/03 08:03:34 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_n(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (line[i] == '\n')
			i++;
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

int	is_rgb(char *line)
{
	char	**line_splitted;
	int		i;
	int		j;
	char	c;
	int		tab_size;

	line_splitted = ft_split(line, ',');
	tab_size = 0;
	while (line_splitted[tab_size])
		tab_size++;
	if (tab_size != 3)
		return (ft_free_array(line_splitted), 0);
	i = -1;
	j = -1;
	while (line_splitted[++i])
	{
		j = -1;
		while (line_splitted[i][++j])
		{
			c = line_splitted[i][j];
			if (!ft_isdigit(c))
				return (ft_free_array(line_splitted), 0);
		}
	}
	return (ft_free_array(line_splitted), 1);
}

char	*ft_strpad(char *str, int len, char pad)
{
	char	*new;
	int		i;

	new = malloc(len + 1);
	i = 0;
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	while (i < len)
		new[i++] = pad;
	new[len] = '\0';
	free(str);
	return (new);
}
