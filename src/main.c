/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:17:21 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 09:37:39 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (printf("error args\n"), 0);
	if (check_map(argv[1]))
		return (printf("error map\n"), 0);
	return (0);
}
