/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/19 16:06:56 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_images(t_game *game)
{
	int	size;

	size = SIZE_CHUNK;
	game->lvl->images[e_ground] = malloc(sizeof(t_pict));
	game->lvl->images[e_wall] = malloc(sizeof(t_pict));
	game->lvl->images[e_collec] = malloc(sizeof(t_pict));
	game->lvl->images[e_player] = malloc(sizeof(t_pict));
	game->lvl->images[e_exit] = malloc(sizeof(t_pict));
	
	game->lvl->images[e_ground]->img = mlx_xpm_file_to_image(game->mlx,
			"assets/default/test.xpm", &size, &size);
	game->lvl->images[e_wall]->img = mlx_xpm_file_to_image(game->mlx,
			"assets/default/default_wall.xpm", &size, &size);
	game->lvl->images[e_collec]->img = mlx_xpm_file_to_image(game->mlx,
			"assets/default/default_collec.xpm", &size, &size);
	game->lvl->images[e_player]->img = mlx_xpm_file_to_image(game->mlx,
			"assets/default/default_player.xpm", &size, &size);
	game->lvl->images[e_exit]->img = mlx_xpm_file_to_image(game->mlx,
			"assets/default/default_exit.xpm", &size, &size);
	// add ennemy
	//if (!game->lvl->images[e_ground] || !game->lvl->images[e_wall] ||
	//	!game->lvl->images[e_collec] || !game->lvl->images[e_player] ||
	//	!game->lvl->images[e_exit])
	//exit(EXIT_FAILURE); // clean exit
}
