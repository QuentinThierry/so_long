/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_forest_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:39:38 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:25:50 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static int	is_all_image_good(t_img **img)
{
	int	i;

	i = 0;
	while (i < e_nb_img)
	{
		if (img[i] == NULL && i != e_debug && i != e_debug_tile)
		{
			printf("i : %d\n", i);
			return (0);
		}
		i++;
	}
	if (ISDEBUG && !(img[e_debug] && img[e_debug_tile]))
		return (0);
	return (1);
}

void	load_images_forest(t_game *game)
{
	t_vector2	map_size;

	game->lvl->images = ft_calloc(sizeof(t_img *), e_nb_img);
	if (!game->lvl->images)
		exit_game(game, "Error\nAllocation error.\n");
	map_size.x = game->lvl->map_size.x * SIZE_CHUNK;
	map_size.y = game->lvl->map_size.y * SIZE_CHUNK;
	game->lvl->images[e_canvas]
		= mlx_new_image(game->mlx, map_size.x, map_size.y);
	game->lvl->images[e_camera]
		= mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_special_images(game);
	load_ground_wall(game);
	load_player_idle(game);
	load_player_run(game);
	load_collec_exit(game);
	load_ennemy_idle1(game);
	_load_ennemy_idle2(game);
	_load_enemy_run(game);
	if (!is_all_image_good(game->lvl->images))
		exit_game(game, "Error\nLoading images error.\n");
}
