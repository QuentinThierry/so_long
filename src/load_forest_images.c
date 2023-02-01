/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_forest_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/01 00:17:21 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	_load_ground1(t_game *game)
{
	game->lvl->images[e_ground0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GRASS, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GRASS, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GRASS, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GRASS, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	_load_ground2(t_game *game)
{
	game->lvl->images[e_ground1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	_load_wall1(t_game *game)
{
	game->lvl->images[e_wall0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	_load_wall2(t_game *game)
{
	game->lvl->images[e_wall2_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_WALL, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	_load_player(t_game *game)
{
	game->lvl->images[e_player_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_player_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_player_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_player_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_player_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	_load_exit(t_game *game)
{
	game->lvl->images[e_exit_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_exit_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

//void	_load_collec(t_game *game)
//{
	
//}

//void	_load_ennemy(t_game *game)
//{
	
//}

void	load_images_forest(t_game *game)
{
	game->lvl->images = malloc(sizeof(t_img *) * e_nb_img);
	// protect
	_load_ground1(game);
	_load_ground2(game);
	_load_wall1(game);
	_load_wall2(game);
	_load_player(game);
	_load_exit(game);
	game->lvl->images[e_background]
		= btmlx_xpm_file_to_image(game->mlx, FOREST_BACKGROUND,
		(t_vector2){SCREEN_WIDTH, SCREEN_HEIGHT});
	//_load_collec(game);
	//_load_ennemy(game);
}

void	init_base_images(t_game *game)
{
	t_vector2	map_size;

	map_size.x = game->lvl->map_size.x * SIZE_CHUNK;
	map_size.y = game->lvl->map_size.y * SIZE_CHUNK;
	game->lvl->images[e_canvas]
		= mlx_new_image(game->mlx, map_size.x, map_size.y);
	game->lvl->images[e_camera]
		= mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}
