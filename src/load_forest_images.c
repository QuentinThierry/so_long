/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_forest_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/10 20:59:02 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_load_ground1(t_game *game)
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
	game->lvl->images[e_ground1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_ground2(t_game *game)
{
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

static void	_load_wall1(t_game *game)
{
	game->lvl->images[e_wall0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_wall2(t_game *game)
{
	game->lvl->images[e_wall2_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall2_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall3_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_player(t_game *game)
{
	game->lvl->images[e_player_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){PLAYER_SIZE, PLAYER_SIZE});
	game->lvl->images[e_player_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){PLAYER_SIZE, PLAYER_SIZE});
	game->lvl->images[e_player_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){PLAYER_SIZE, PLAYER_SIZE});
	game->lvl->images[e_player_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){PLAYER_SIZE, PLAYER_SIZE});
	game->lvl->images[e_player_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_BEE, (t_vector2){PLAYER_SIZE, PLAYER_SIZE});
}

static void	_load_exit(t_game *game)
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

static void	_load_collec1(t_game *game)
{
	game->lvl->images[e_collec0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_R, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_R, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_R, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_R, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_R, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_collec2(t_game *game)
{
	game->lvl->images[e_collec2_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec2_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec2_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec2_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec2_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_Y, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec3_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_D, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec3_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_D, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec3_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_D, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec3_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_D, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec3_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_FLOWER_D, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_ennemy(t_game *game)
{
	game->lvl->images[e_enemy_0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST_A, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST_A, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST_A, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST_A, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST_A, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_ennemy2(t_game *game)
{
	game->lvl->images[e_enemy_2_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_2_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_2_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_2_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_2_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_3_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_3_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_3_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_3_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_3_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GHOST, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	load_images_forest(t_game *game)
{
	game->lvl->images = ft_calloc(sizeof(t_img *), e_nb_img);
	// protect
	_load_ground1(game);
	_load_ground2(game);
	_load_wall1(game);
	_load_wall2(game);
	_load_player(game);
	_load_exit(game);
	_load_collec1(game);
	_load_collec2(game);
	_load_ennemy(game);
	_load_ennemy2(game);
	game->lvl->images[e_background]
		= btmlx_xpm_file_to_image(game->mlx, FOREST_BACKGROUND,
		(t_vector2){SCREEN_WIDTH, SCREEN_HEIGHT});
	if (ISDEBUG)
	{
		game->lvl->images[e_debug]
			= mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		game->lvl->images[e_debug_tile]
			= btmlx_xpm_file_to_image(game->mlx, DEBUG_TILE,
			(t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	}
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
