/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/xx/xx xx:xx:xx by your_login       #+#    #+#             */
/*   Updated: 2024/xx/xx xx:xx:xx by your_login      #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D map_file.cub\n");
		return (1);
	}
	(void)argv;
	return (0);
}
