/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 19:36:00 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_images_forest(t_game *game)
{
	game->lvl->sprites[e_ground] = malloc(sizeof(t_sprite));
	pre_init_variants(game->lvl->sprites[e_ground]);
	game->lvl->sprites[e_wall] = malloc(sizeof(t_sprite));
	pre_init_variants(game->lvl->sprites[e_wall]);
	// game->lvl->sprites[e_collec] = malloc(sizeof(t_sprite));
	// pre_init_variants(game->lvl->sprites[e_collec]);
	game->lvl->sprites[e_exit] = malloc(sizeof(t_sprite));
	pre_init_variants(game->lvl->sprites[e_exit]);

	game->lvl->sprites[e_ground]->var[0] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_ground]->var[0]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/forest/forest_ground.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_ground]->var[1] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_ground]->var[1]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/forest/forest_grass.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_ground]->var[2] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_ground]->var[2]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/forest/forest_stick.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_ground]->var[3] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_ground]->var[3]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/forest/forest_stone.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_ground]->var[4] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_ground]->var[4]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/forest/forest_ground.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});


	game->lvl->sprites[e_wall]->var[0] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[0]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_wall]->var[1] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[1]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_wall]->var[2] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[2]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_wall]->var[2] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[2]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_wall]->var[3] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[3]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_wall]->var[4] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_wall]->var[4]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_wall.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});

	// game->lvl->sprites[e_collec]->var[0] = malloc(sizeof(t_pict));
	// game->lvl->sprites[e_collec]->var[0]->img = btmlx_xpm_file_to_image(game->mlx,
	// 	"assets/default/default_collec.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
			
	game->lvl->sprites[e_exit]->var[0] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_exit]->var[0]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_exit]->var[1] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_exit]->var[1]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_exit]->var[2] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_exit]->var[2]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_exit]->var[3] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_exit]->var[3]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->sprites[e_exit]->var[4] = malloc(sizeof(t_pict));
	game->lvl->sprites[e_exit]->var[4]->img = btmlx_xpm_file_to_image(game->mlx,
		"assets/default/default_exit.xpm", (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}
