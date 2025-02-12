/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:58:59 by nopareti          #+#    #+#             */
/*   Updated: 2025/02/11 15:14:40 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void play_sound(const char *path)
{
    char command[256];
    snprintf(command, sizeof(command), "aplay %s > /dev/null 2>&1 &", path);
    system(command);
}

t_texture	init_xpm_texture(t_game *game, char *filename)
{
    t_texture   texture;

    
	texture.img = mlx_xpm_file_to_image(game->mlx, filename, &texture.width, &texture.height);
	texture.addr = (int *)mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.size_line, &texture.endian);
    return (texture);
}

void draw_texture_on_screen(t_game *game, t_texture tex, int scale, int draw_x, int draw_y)
{
    int target_width = tex.width * scale;
    int target_height = tex.height * scale;
    double scale_x = (double)tex.width / target_width;  // Inverse du calcul original
    double scale_y = (double)tex.height / target_height;  // Inverse du calcul original

    for (int y = 0; y < target_height; y++) 
    {
        for (int x = 0; x < target_width; x++) 
        {
            // Calculer les coordonnées dans la texture d'origine
            int src_x = (int)(x * scale_x);
            int src_y = (int)(y * scale_y);

            if (src_x >= 0 && src_x < tex.width && src_y >= 0 && src_y < tex.height) 
            {
                int color = tex.addr[src_y * tex.width + src_x];  // Récupérer la couleur du pixel de la texture

                // Vérifier si la couleur n'est pas transparente (on suppose ici que l'alpha est dans les bits les plus significatifs)
                if ((color & 0x00FFFFFF) != 0) 
                {
                    // Vérifier si les coordonnées de dessin sont dans les limites de l'écran
                    if (draw_x + x >= 0 && draw_x + x < game->screen_width && draw_y + y >= 0 && draw_y + y < game->screen_height) 
                    {
                        // Affecter la couleur à l'écran (ajouter x et y à draw_x et draw_y)
                        game->screen_buffer[draw_y + y][draw_x + x] = color;
                    }
                }
            }
        }
    }
}
