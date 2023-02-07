/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/07 18:16:06 by qthierry         ###   ########.fr       */
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

void	draw_rectangle(t_sprite *pict, t_vector2 pos, t_vector2 size, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < size.x && x < pict->size.x)
	{
		y = 0;
		while (y < size.y && x < pict->size.y)
		{
			my_mlx_pixel_put(pict, pos.x + x, pos.y + y, color);
			++y;
		}
		++x;
	}
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

t_enemy	*instantiate_enemy(t_img **images, int id)
{
	t_enemy *enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->id = id;
	enemy->is_triggered = 0;
	enemy->sprite = malloc(sizeof(t_sprite));
	if (!enemy->sprite)
		return (free(enemy), NULL);
	enemy->sprite->image_id = e_enemy_0_0;
	btmlx_get_addr(enemy->sprite, images[e_enemy_0_0]);
	enemy->pos = &enemy->sprite->pos;
	enemy->size = &enemy->sprite->size;
	enemy->collider = malloc(sizeof(t_collider));
	if (!enemy->collider)
		return (free(enemy->sprite), free(enemy), NULL);
	enemy->collider->id = id;
	enemy->collider->has_been_triggered = 0;
	enemy->collider->image_id = &enemy->sprite->image_id;
	enemy->collider->pos = enemy->pos;
	enemy->collider->size = enemy->size;
	return (enemy);
}

int	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	nb_enemies;

	i = 0;
	nb_enemies = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		if (game->lvl->map[i] == 'G')
			nb_enemies++;
		i++;
	}
	game->lvl->enemies = malloc(sizeof(t_enemy *) * (nb_enemies + 1));
	if (!game->lvl->enemies)
		return (0);
	i = 0;
	j = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		if (game->lvl->map[i] == 'G')
		{
			game->lvl->enemies[j] = instantiate_enemy(game->lvl->images, j);
			if (!game->lvl->enemies[j])
				return (0);
			*game->lvl->enemies[j]->pos = game->lvl->canvas->chunks[i].pos;
			game->lvl->enemies[j]->exact_pos = (t_fvector2)
			{
				game->lvl->enemies[j]->pos->x,
				game->lvl->enemies[j]->pos->y
			};
			game->lvl->enemies[j]->dir = (t_fvector2){1, 1};
			j++;
		}
		i++;
	}
	game->lvl->enemies[nb_enemies] = NULL;
	return (1);
}

void	move_enemy(t_game *game, int id, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
	if (!game->lvl->enemies[id]->dir.x && !game->lvl->enemies[id]->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->enemies[id]->exact_pos.x +
				game->lvl->enemies[id]->dir.x * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.x = new_posx;
		game->lvl->enemies[id]->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->enemies[id]->exact_pos.y +
				game->lvl->enemies[id]->dir.y * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.y = new_posy;
		game->lvl->enemies[id]->pos->y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
}

void	reverse_move_enemy(t_game *game, int id, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
	if (!game->lvl->enemies[id]->dir.x && !game->lvl->enemies[id]->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->enemies[id]->exact_pos.x -
				game->lvl->enemies[id]->dir.x * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.x = new_posx;
		game->lvl->enemies[id]->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->enemies[id]->exact_pos.y -
				game->lvl->enemies[id]->dir.y * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.y = new_posy;
		game->lvl->enemies[id]->pos->y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
}

int	is_inside_load_range(t_game *game, t_vector2 pos)
{
	return (pos.x > game->lvl->cam->pos.x - OFFSET_CAM_LOAD
		&& pos.x < game->lvl->cam->pos.x
			+ game->lvl->cam->size.x + OFFSET_CAM_LOAD
		&& pos.y < game->lvl->cam->pos.y
			+ game->lvl->cam->size.y + OFFSET_CAM_LOAD
		&& pos.y > game->lvl->cam->pos.y - OFFSET_CAM_LOAD);
}

void	check_trigger_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (!game->lvl->enemies[i]->is_triggered
			&& is_inside_load_range(game, *game->lvl->enemies[i]->pos))
		{
			if (distance(*game->lvl->enemies[i]->pos, *game->lvl->player->pos)
				< DISTANCE_AGGRO)
			{
				game->lvl->enemies[i]->is_triggered = 1;
				game->lvl->enemies[i]->sprite->image_id = e_enemy_1_0;
			}
			else
				game->lvl->enemies[i]->sprite->image_id = e_enemy_0_0;
		}
		else
			game->lvl->enemies[i]->is_triggered = 0;
		++i;
	}
}

void	calculate_dir(t_game *game, int id)
{
	game->lvl->enemies[id]->dir = direction_normalized(*game->lvl->enemies[id]->pos, *game->lvl->player->pos);
}

void	enemy_movement(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (game->lvl->enemies[i]->is_triggered)
		{
			calculate_dir(game, i);
			move_enemy(game, i, 1, 0);
			if (check_wall_collision(game->lvl, game->lvl->enemies[i]->collider))
				reverse_move_enemy(game, i, 1, 0);
			move_enemy(game, i, 0, 1);
			if (check_wall_collision(game->lvl, game->lvl->enemies[i]->collider))
				reverse_move_enemy(game, i, 0, 1);
		}
		i++;
	}
}



void	move_camera_on_player(t_sprite *cam, t_vector2 player_pos)
{
	cam->pos = (t_vector2) {
		player_pos.x - SCREEN_WIDTH / 2,
		player_pos.y - SCREEN_HEIGHT / 2};
}

int	on_update(t_game *game)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	if (game->lvl->is_animating_cam)
		camera_animation_to_exit(game);
	else
	{
		player_movement(game);
		move_camera_on_player(game->lvl->cam, *game->lvl->player->pos);
		check_trigger_enemy(game);
		enemy_movement(game);
		check_col_enemy(game);
		check_col_collectible(game);
		check_col_exit(game);
	}

	recalculate_chunks(game->lvl);
	if (ISDEBUG)
		debug_calculate(game->lvl);
	draw_on_window(game);

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
	game.lvl = malloc(sizeof(t_level));

	game.lvl->map = map;
	game.lvl->map_size = map_size;
	
	load_images_forest(&game);
	init_base_images(&game);
	init_lvl_base(&game);

	game.fps = 10;
	game.elapsed = 0;
	game.press_on_key[e_W] = &press_on_w;
	game.press_on_key[e_A] = &press_on_a;
	game.press_on_key[e_S] = &press_on_s;
	game.press_on_key[e_D] = &press_on_d;
	game.press_on_key[e_P] = &press_on_p;
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

	//mlx_do_key_autorepeaton(game.mlx);
	return (0);
}
