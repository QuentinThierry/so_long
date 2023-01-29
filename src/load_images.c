/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/29 21:22:49 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_images_default(t_game *game)
{
	game->lvl->images[e_ground] = malloc(sizeof(t_pict));
	game->lvl->images[e_wall] = malloc(sizeof(t_pict));
	game->lvl->images[e_collec] = malloc(sizeof(t_pict));
	game->lvl->images[e_exit] = malloc(sizeof(t_pict));
	
	game->lvl->images[e_ground]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_ground.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_collec.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	// add ennemy
	//if (!game->lvl->images[e_ground] || !game->lvl->images[e_wall] ||
	//	!game->lvl->images[e_collec] || !game->lvl->images[e_player] ||
	//	!game->lvl->images[e_exit])
	//exit(EXIT_FAILURE); // clean exit
}

void	load_images_forest(t_game *game)
{
	game->lvl->images[e_ground] = malloc(sizeof(t_pict));
	game->lvl->images[e_wall] = malloc(sizeof(t_pict));
	game->lvl->images[e_collec] = malloc(sizeof(t_pict));
	game->lvl->images[e_exit] = malloc(sizeof(t_pict));
	 
	game->lvl->images[e_ground]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/forest/forest_grass.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_collec.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit]->img = btmlx_xpm_file_to_image(game->mlx,
			"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	// add ennemy
	//if (!game->lvl->images[e_ground] || !game->lvl->images[e_wall] ||
	//	!game->lvl->images[e_collec] || !game->lvl->images[e_player] ||
	//	!game->lvl->images[e_exit])
	//exit(EXIT_FAILURE); // clean exit
}
