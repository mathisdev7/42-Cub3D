/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:18:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/05 15:57:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
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
	while (argv[1][i])
	{
		if (argv[1][i] == '.')
			if (argv[1][i + 1] == 'c' && argv[1][i + 2] == 'u' && argv[1][i
				+ 3] == 'b')
				return (0);
		i++;
	}
	return (1);
}
