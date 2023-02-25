/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:44:44 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	update_player_2(t_game *game)
{
	player_movement(game, game->lvl->player2);
	draw_arrow_to_end(game->lvl, game->lvl->player2);
	check_trigger_enemy(game, game->lvl->player2);
}

static void	on_update2(t_game *game)
{
	play_animations(game);
	recalculate_chunks(game->lvl);
	draw_on_window(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->lvl->cam->sprite->img_ptr, 0, 0);
	draw_ui(game);
	clear_chunks_to_redraw(game->lvl->canvas);
	calculate_fps(&game->fps, &game->elapsed);
	game->tot_fps += game->fps;
	game->tot_frame++;
}

int	on_update(t_game *game)
{
	if (game->lvl->is_animating_cam)
		camera_animation_to_exit(game->lvl);
	else if (!game->is_end)
	{
		player_movement(game, game->lvl->player1);
		check_trigger_enemy(game, game->lvl->player1);
		if (game->lvl->player2)
			update_player_2(game);
		update_cam_pos(game);
		enemy_movement(game);
		check_col_enemy(game);
		check_col_collectible(game);
		check_col_exit(game);
	}
	else
	{
		find_chunk_under(game->lvl->canvas, game->lvl->player1->sprite);
		if (game->lvl->player2)
			find_chunk_under(game->lvl->canvas, game->lvl->player2->sprite);
	}
	on_update2(game);
	return (0);
}

int	on_start(t_game *game, char *map, t_vector2 map_size)
{
	*game = init_values(map, map_size);
	game->lvl->canvas->origin = (t_vector2){0, 0};
	init_chunks(game);
	init_map_variables(game);
	if (!init_enemies(game->lvl))
		exit_game(game, "Error\nAllocation error.\n");
	if (!init_collisions(game->lvl))
		exit_game(game, "Error\nAllocation error.\n");
	init_ui(game);
	gettimeofday(&game->lvl->start_time, NULL);
	game->lvl->is_animating_cam = HAS_CAM_ANIM;
	init_dist_table(game->lvl, game->lvl->dist_table, map_size.x * map_size.y);
	if (check_valid_path(game) != 1)
		exit_game(game, "Error\nMap entry is not valid.\n");
	game->window
		= mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so_long");
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_game		game;
	char		*map;
	t_vector2	map_size;
	int			seed;

	if (!SEED)
		seed = time(NULL);
	if (argc == 0 || argc > 2)
		return (1);
	ft_bzero(&game, sizeof(game));
	game.window = NULL;
	if (!parse_map(argv[1], &map, &map_size))
		exit_game(&game, "Error\nMap entry is not valid.\n");
	srand((unsigned int)seed);
	if (on_start(&game, map, map_size))
		return (1);
	mlx_hook(game.window, KeyPress, KeyPressMask, &press_key, &game);
	mlx_hook(game.window, KeyRelease, KeyReleaseMask, &release_key, &game);
	mlx_loop_hook(game.mlx, on_update, &game.mlx);
	mlx_loop(game.mlx);
	mlx_do_key_autorepeaton(game.mlx);
	return (0);
}

// show fps on screen :
// add in 'on_update' at begin to draw_fps on screen
//static unsigned int	frame = 0;
//static int			fps = 0;

//if (!frame && !fps)
//	calculate_fps(&game->fps, &game->elapsed);

// this at end
//if (frame % FRAME_RATE_DRAW_SPEED == 0)
//{
//	fps = game->fps;
//	frame = 0;
//}
//frame++;
//show_fps(game, (t_vector2){FPS_POSX, FPS_POSY}, fps);
