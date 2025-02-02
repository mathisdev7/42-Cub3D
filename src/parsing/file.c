/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:06:20 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/01 20:12:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_dir(char *arg)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(arg, 00200000);
	if (fd >= 0)
	{
		close(fd);
		ret = 1;
	}
	return (ret);
}

static int	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p' || arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (0);
	return (1);
}

int	check_file(char *arg)
{
	int	fd;

	if (is_dir(arg))
		return (1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	if (!is_xpm_file(arg))
		return (1);
	return (0);
}
