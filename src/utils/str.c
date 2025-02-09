/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:45:39 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/09 14:12:06 by mazeghou         ###   ########.fr       */
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

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_color(char *color)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	colors = ft_split(color, ',');
	if (!colors)
		return (0);
	if (ft_array_len(colors) != 3)
		return (ft_free_array(colors), 0);
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (colors[i][j] < '0' || colors[i][j] > '9')
				return (ft_free_array(colors), 0);
			j++;
		}
		i++;
	}
	ft_free_array(colors);
	return (1);
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
