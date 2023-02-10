/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/10 21:36:18 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>

void	my_mlx_pixel_put(t_sprite *sprite, int x, int y, unsigned int color)
{
	char	*dst;

	dst = sprite->img_ptr->data +
		(y * sprite->line_length + x * sprite->opp);
	*(unsigned int*)dst = color;
}

void	calculate_fps(int *fps, double *elapsed)
{
	static struct timeval	prev_time = {0, 0};
	struct timeval			tmp;
	double					delay;

	if (!prev_time.tv_sec)
		gettimeofday(&prev_time, NULL);
	gettimeofday(&tmp, NULL);
	delay = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC)
			+ tmp.tv_sec - prev_time.tv_sec);
	while (delay < FPS_VSYNC)
	{
		gettimeofday(&tmp, NULL);
		delay = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC)
			+ tmp.tv_sec - prev_time.tv_sec);
	}
	*elapsed = delay;
	*fps = (int)(1.0 / *elapsed);
	prev_time = tmp;
}

// a changer
void	show_fps(t_game *game, t_vector2 pos, int fps)
{
	int	i = 0;
	int	j = 0;
	while (j < FPS_HEIGHT)
	{
		i = 0;
		while (i < FPS_WIDTH)
			mlx_pixel_put(game->mlx, game->window, FPS_POSX + i++, FPS_POSY - j, WHITE);
		j++;
	}
	
	mlx_string_put(game->mlx, game->window, pos.x,
		pos.y, FPS_COLOR, ft_itoa(fps));
}

void	init_map_variables(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		game->lvl->canvas->chunks_to_redraw[i] = 1;
		if (game->lvl->map[i] == 'P')
		{
			*game->lvl->player->pos = game->lvl->canvas->chunks[i].pos;
			game->lvl->player->exact_pos.x = game->lvl->player->pos->x;
			game->lvl->player->exact_pos.y = game->lvl->player->pos->y;
		}
		if (game->lvl->map[i] == 'C')
			game->lvl->max_collec++;
		i++;
	}
	recalculate_chunks(game->lvl);
	clear_chunks_to_redraw(game->lvl->canvas);
}

int	is_inside_load_range(t_game *game, t_vector2 pos)
{
	return (pos.x > game->lvl->cam->pos->x - OFFSET_CAM_LOAD
		&& pos.x < game->lvl->cam->pos->x
			+ game->lvl->cam->size->x + OFFSET_CAM_LOAD
		&& pos.y < game->lvl->cam->pos->y
			+ game->lvl->cam->size->y + OFFSET_CAM_LOAD
		&& pos.y > game->lvl->cam->pos->y - OFFSET_CAM_LOAD);
}

void	move_camera_on_player(t_camera *cam, t_vector2 player_pos)
{
	*cam->pos = (t_vector2){
		player_pos.x - SCREEN_WIDTH / 2 + PLAYER_SIZE / 2,
		player_pos.y - SCREEN_HEIGHT / 2 + PLAYER_SIZE / 2};
	cam->exact_pos = (t_fvector2){cam->pos->x, cam->pos->y};
}

int	on_update(t_game *game)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	// a_star(game, game->lvl->player);
	// game->lvl->exit_chunk = rand() % (game->lvl->map_size.x * game->lvl->map_size.y);
	if (game->lvl->is_animating_cam)
		camera_animation_to_exit(game);
	else
	{
		player_movement(game);
		if (game->lvl->cam->is_cam_lock == 1)
			move_camera_on_player(game->lvl->cam, *game->lvl->player->pos);
		else
			move_camera(game);
		check_trigger_enemy(game);
		enemy_movement(game);
		check_col_enemy(game);
		check_col_collectible(game);
		check_col_exit(game);
	}
	
	recalculate_chunks(game->lvl);
	draw_on_window(game);
	clear_chunks_to_redraw(game->lvl->canvas);

	calculate_fps(&game->fps, &game->elapsed);
	if (frame % FRAME_RATE_DRAW_SPEED == 0)
	{
		fps = game->fps;
		frame = 0;
	}
	show_fps(game, (t_vector2){FPS_POSX, FPS_POSY}, fps);
	frame++;
	return (0);
}

t_game	init_values(char *map, t_vector2 map_size)
{
	t_game	game;

	game.mlx = mlx_init();
	game.lvl = ft_calloc(sizeof(t_level), 1);

	game.lvl->map = map;
	game.lvl->map_size = map_size;
	game.lvl->exit_chunk = find_exit_chunk(game.lvl->map);
	
	load_images_forest(&game);
	init_base_images(&game);
	init_lvl_base(&game);

	game.fps = 120;
	game.elapsed = 0;
	game.press_on_key[e_W] = &press_on_w;
	game.press_on_key[e_A] = &press_on_a;
	game.press_on_key[e_S] = &press_on_s;
	game.press_on_key[e_D] = &press_on_d;
	game.press_on_key[e_P] = &press_on_p;
	game.press_on_key[e_L] = &press_on_l;
	game.press_on_key[e_UA] = &press_on_ua;
	game.press_on_key[e_LA] = &press_on_la;
	game.press_on_key[e_DA] = &press_on_da;
	game.press_on_key[e_RA] = &press_on_ra;
	game.press_on_key[e_ESC] = &press_on_esc;
	return (game);
}

int	on_start(t_game *game, char *map, t_vector2 map_size)
{
	*game = init_values(map, map_size);

	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so_long");

	// others
	game->lvl->canvas->origin = (t_vector2){0, 0};
	
	init_chunks(game->lvl);
	init_map_variables(game);
	init_enemies(game);
	init_collisions(game->lvl);

	gettimeofday(&game->lvl->start_time, NULL);

	game->lvl->is_animating_cam = HAS_CAM_ANIM;
	a_star(game, game->lvl->player);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_game		game;
	char		*map;
	t_vector2	map_size;
	int			seed;

	if (!SEED)
		seed = time(NULL);
	if (argc == 0 || argc > 2)
		return (1);
	if (!parse_map(argv[1], &map, &map_size))
	{
		argc = write(1, "Error\nMap entry is not valid.\n", 30);
		return (1);
	}
	srand((unsigned int)seed);
	if(on_start(&game, map, map_size))
		return (1);
	mlx_hook(game.window, KeyPress, KeyPressMask, &press_key, &game);
	mlx_hook(game.window, KeyRelease, KeyReleaseMask, &release_key, &game);
	mlx_loop_hook(game.mlx, on_update, &game.mlx);
	mlx_loop(game.mlx);

	mlx_do_key_autorepeaton(game.mlx);
	return (0);
}
