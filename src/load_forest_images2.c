/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_forest_images2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:23:45 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:27:03 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_ground_wall(t_game *game)
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

void	load_player_idle(t_game *game)
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

void	load_player_run(t_game *game)
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

void	load_collec_exit(t_game *game)
{
	game->lvl->images[e_collec0] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_ACORN, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
	game->lvl->images[e_collec1] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_ACORN_EMPT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
		game->lvl->images[e_exit] = btmlx_xpm_file_to_image(game->mlx,
			FOREST_EXIT, (t_vector2){SIZE_CHUNK, SIZE_CHUNK});
}

void	load_ennemy_idle1(t_game *game)
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
