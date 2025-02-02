/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:45:39 by mazeghou          #+#    #+#             */
/*   Updated: 2025/02/02 12:45:43 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
