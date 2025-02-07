/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:18:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/07 10:28:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	has_cub_extension(const char *filename)
{
	int	len;

	len = strlen(filename);
	return (len > 4 && ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D map_file.cub\n");
		return (1);
	}
	if (file_exists(argv[1]) == 0)
	{
		printf("Error\nMap file not found\n");
		return (1);
	}
	if (!has_cub_extension(argv[1]))
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (1);
	}
	return (0);
}
