/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_forest_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/24 16:16:17 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_load_ground_wall(t_game *game)
{
	game->lvl->images[e_ground0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GROUND, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_GRASS, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STICK, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_ground3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_STONE, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_wall1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_TREE2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_player_idle(t_game *game)
{
	game->lvl->images[e_player_idle_0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_0, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_1, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_2, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_3, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_4, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_0_5] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE0_5, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_0, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_1, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_2, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_3, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_4, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_idle_1_5] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_IDLE1_5, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
}

static void	_load_player_run(t_game *game)
{
	game->lvl->images[e_player_run_0_0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_0, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_1, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_2] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_2, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_3] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_3, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_4] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_4, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_5] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_5, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_6] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_6, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
	game->lvl->images[e_player_run_0_7] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_SQR_RUN0_7, (t_vector2){PLAYER_WIDTH, PLAYER_HEIGHT});
}

static void	_load_collec_exit(t_game *game)
{
	game->lvl->images[e_collec0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_ACORN, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_ACORN_EMPT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
		game->lvl->images[e_exit] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_ennemy_idle1(t_game *game)
{
	game->lvl->images[e_enemy_idle_0_0] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE0_0, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_0_1] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE0_1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_0_2] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE0_2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_0_3] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE0_3, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_0_4] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE0_4, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_0] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_0, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_1] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_2] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_3] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_3, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_4] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_4, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_ennemy_idle2(t_game *game)
{
	game->lvl->images[e_enemy_idle_1_5] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_5, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_6] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_6, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_7] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_7, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_8] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_8, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_9] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_9, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_10] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_10, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_11] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_11, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_12] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_12, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_idle_1_13] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_IDLE1_13, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	_load_enemy_run(t_game *game)
{
	game->lvl->images[e_enemy_run_0_0] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_RUN0_0, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_run_0_1] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_RUN0_1, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_run_0_2] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_RUN0_2, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_run_0_3] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_RUN0_3, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_enemy_run_0_4] = btmlx_xpm_file_to_image(game->mlx,
			SLIME_B_RUN0_4, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

static void	load_special_images(t_game *game)
{
	game->lvl->images[e_background]
		= btmlx_xpm_file_to_image(game->mlx, FOREST_BACKGROUND,
			(t_vector2){SCREEN_WIDTH, SCREEN_HEIGHT});
	game->lvl->images[e_arrow]
		= btmlx_xpm_file_to_image(game->mlx, FOREST_EXIT,
			(t_vector2){SIZE_CHUNK / 4, SIZE_CHUNK / 4});
	game->lvl->images[e_ui]
		= btmlx_xpm_file_to_image(game->mlx, UI,
			(t_vector2){SCREEN_WIDTH / UI_RATIO, SCREEN_HEIGHT
			/ (2.5 * UI_RATIO)});
	game->lvl->images[e_end_screen]
		= mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!ISDEBUG)
		return ;
	game->lvl->images[e_debug]
		= mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->lvl->images[e_debug_tile]
		= btmlx_xpm_file_to_image(game->mlx, DEBUG_TILE,
			(t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	load_images_forest(t_game *game)
{
	game->lvl->images = ft_calloc(sizeof(t_img *), e_nb_img);
	load_special_images(game);
	_load_ground_wall(game);
	_load_player_idle(game);
	_load_player_run(game);
	_load_collec_exit(game);
	_load_ennemy_idle1(game);
	_load_ennemy_idle2(game);
	_load_enemy_run(game);
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
