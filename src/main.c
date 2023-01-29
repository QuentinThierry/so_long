/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/29 21:28:59 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_pict *pict, int x, int y, unsigned int color)
{
	char	*dst;

	dst = pict->addr + (y * pict->line_length + x * pict->opp);
	*(unsigned int*)dst = color;
}

enum e_key_map	get_key(int key)
{
	if (key == KEY_W)
		return (e_W);
	if (key == KEY_A)
		return (e_A);
	if (key == KEY_S)
		return (e_S);
	if (key == KEY_D)
		return (e_D);
	if (key == KEY_E)
		return (e_E);
	if (key == KEY_ESC)
		return (e_ESC);
	return (NB_KEYS);
}

int	press_key(int key, t_game *game)
{
	enum e_key_map e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 0);
	return (0);
}


int release_key(int key, t_game *game)
{
	enum e_key_map e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 1);
	return (0);
}

void	calculate_fps(int *fps, double *elapsed)
{
	static struct timeval	prev_time = {0, 0};
	struct timeval			tmp;
	double					delay;

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

void	draw_rectangle(t_pict *pict, t_vector2 pos, t_vector2 size, int color)
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

int	init_background(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		game->lvl->canvas->chunks_to_redraw[i] = 1;
		if (game->lvl->map[i] == 'P')
		{
			game->lvl->canvas->origin.x = (SCREEN_WIDTH / 2 - game->lvl->images[e_player]->size.x / 2) - (i % game->lvl->canvas->nb_chunks.x) * SIZE_CHUNK;
			game->lvl->canvas->origin.y = (SCREEN_HEIGHT / 2 - game->lvl->images[e_player]->size.y / 2) - (i / game->lvl->canvas->nb_chunks.x) * SIZE_CHUNK;
			game->lvl->canvas->exact_origin.x = game->lvl->canvas->origin.x;
			game->lvl->canvas->exact_origin.y = game->lvl->canvas->origin.y;
		}
		i++;
	}
	recalculate_chunks(game->lvl);
	clear_chunks_to_redraw(game->lvl->canvas);
	return (0);
}

void	move_pixel(t_pict *pict, t_vector2 delta)
{
	int				x;
	int				y;

	y = 0;
	while (y < pict->size.y)
	{
		x = 0;
		while (x < pict->size.x)
		{
			if (!(x + delta.x > pict->size.x && y + delta.y > pict->size.y))
			{
				memmove(
					pict->addr + (y * pict->line_length)
								+ (x * pict->opp),
					pict->addr + ((y + delta.y) * pict->line_length)
								+ ((x + delta.x) * pict->opp),
					delta.x
				);
				x++;
			}
		}
		y++;
	}
}

int	draw_layers(t_game *game)
{
	// draw_image_on_canvas(game->lvl->cadraw_image_on_canvas()nvas, game->lvl->images[e_background], (t_vector2){0, 0}, 0);
	recalculate_chunks(game->lvl);
	if (ISDEBUG)
		debug_calculate(game->lvl);

	// draw_image_on_canvas(game->lvl->canvas, game->lvl->images[e_background], (t_vector2){0, 0}, 0);

	draw_image_on_canvas(game->lvl->canvas, game->lvl->images[e_player], game->lvl->images[e_player]->pos, 1);
	// draw_image_on_canvas(game->lvl->canvas, game->lvl->canvas->pict, (t_vector2){0, 0}, 0);
	// mlx_put_image_to_window(game->mlx, game->window, game->lvl->canvas->pict->img, game->lvl->canvas->draw_pos.x, game->lvl->canvas->draw_pos.y);
	// mlx_put_image_to_window(game->mlx, game->window, game->lvl->canvas->pict->img, game->lvl->canvas->draw_pos.x, game->lvl->canvas->draw_pos.y);
	render_camera(game->lvl, (t_vector2) {
		game->lvl->player->pos->x - SCREEN_WIDTH / 2,
		game->lvl->player->pos->y - SCREEN_HEIGHT / 2});
	mlx_put_image_to_window(game->mlx, game->window, game->lvl->camera->img, 0, 0);
	// clear_chunks_to_redraw(game->lvl->canvas);
	return (0);
}

void	update_player_pos(t_game *game)
{
	game->lvl->images[e_player]->pos = (t_vector2)
	{
		(SCREEN_WIDTH / 2 - game->lvl->images[e_player]->size.x / 2) - game->lvl->canvas->origin.x,
		(SCREEN_HEIGHT / 2 - game->lvl->images[e_player]->size.y / 2) - game->lvl->canvas->origin.y
	};
	game->lvl->player->collider->min = game->lvl->images[e_player]->pos;
	game->lvl->player->collider->size = game->lvl->images[e_player]->size;
	game->lvl->player->collider->max = (t_vector2)
	{
		game->lvl->player->collider->min.x + game->lvl->images[e_player]->size.x,
		game->lvl->player->collider->min.y + game->lvl->images[e_player]->size.y
	};
}

int	on_update(t_game *game)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	move_player(game, 1, 0);
	update_player_pos(game);
	if (check_player_collision(game->lvl))
	{
		reverse_move_player(game, 1, 0);
		update_player_pos(game);
	}
	move_player(game, 0, 1);
	update_player_pos(game);
	if (check_player_collision(game->lvl))
	{
		reverse_move_player(game, 0, 1);
		update_player_pos(game);
	}
	draw_layers(game);


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

t_game	init_values()
{
	t_game	game;

	game.mlx = NULL;
	game.window = NULL;
	game.lvl = malloc(sizeof(t_level));
	game.lvl->canvas = malloc(sizeof(t_canvas));
	game.lvl->canvas->pict = malloc(sizeof(t_pict));
	game.lvl->canvas->origin = (t_vector2){0, 0};
	game.lvl->canvas->exact_origin = (t_fvector2){0., 0.};
	game.lvl->images[e_fps] = malloc(sizeof(t_pict));
	game.lvl->images[e_player] = malloc(sizeof(t_pict));
	game.lvl->images[e_ground] = malloc(sizeof(t_pict));
	game.lvl->images[e_background] = malloc(sizeof(t_pict));
	game.lvl->camera = malloc(sizeof(t_pict));
	game.lvl->player = malloc(sizeof(t_player));
	game.lvl->player->collider = malloc(sizeof(t_collider));
	game.lvl->player->pos = &game.lvl->images[e_player]->pos;
	game.lvl->player->dir.x = 0;
	game.lvl->player->dir.y = 0;
	game.lvl->map = NULL;
	game.elapsed = 0;
	game.press_on_key[e_W] = &press_on_w;
	game.press_on_key[e_A] = &press_on_a;
	game.press_on_key[e_S] = &press_on_s;
	game.press_on_key[e_D] = &press_on_d;
	game.press_on_key[e_E] = &press_on_e;
	game.press_on_key[e_ESC] = &press_on_w;
	game.fps = 10;
	return (game);
}

int	on_start(t_game *game, char *map, t_vector2 map_size)
{
	int	main_x;
	int	main_y;

	*game = init_values();
	// init general
	game->mlx = mlx_init();
	
	// init map
	game->lvl->map = map;
	game->lvl->map_size = map_size;
	main_x = map_size.x * SIZE_CHUNK;
	main_y = map_size.y * SIZE_CHUNK;

	// init images and window
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so_long");
	game->lvl->canvas->pict->img = mlx_new_image(game->mlx, main_x, main_y);
	game->lvl->camera->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->lvl->images[e_fps]->img = mlx_new_image(game->mlx, FPS_WIDTH, FPS_HEIGHT);
	game->lvl->images[e_player]->img = mlx_xpm_file_to_image(game->mlx, "assets/cube.xpm", &game->lvl->images[e_player]->size.x, &game->lvl->images[e_player]->size.y);
	game->lvl->images[e_background]->img = btmlx_xpm_file_to_image(game->mlx, "assets/default/default_background.xpm", (t_vector2){SCREEN_WIDTH, SCREEN_HEIGHT});

	// others
	game->lvl->canvas->origin = (t_vector2){0, 0};
	update_player_pos(game);
	// mlx_do_key_autorepeaton(game->mlx);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_game		game;
	char		*map;
	t_vector2	map_size;

	if (argc == 0 || argc > 2)
		return (1);
	if (!parse_map(argv[1], &map, &map_size))
	{
		write(1, "Error\nMap entry is not valid.\n", 30);
		return (1);
	}
	if(on_start(&game, map, map_size))
		return (1);
	//load_images_default(&game);
	load_images_forest(&game);
	btmlx_get_data_addr(game.lvl->canvas->pict);
	btmlx_get_data_addr(game.lvl->images[e_fps]);
	btmlx_get_data_addr(game.lvl->images[e_player]);
	btmlx_get_data_addr(game.lvl->images[e_wall]);
	btmlx_get_data_addr(game.lvl->images[e_ground]);
	btmlx_get_data_addr(game.lvl->images[e_exit]);
	btmlx_get_data_addr(game.lvl->images[e_background]);
	btmlx_get_data_addr(game.lvl->camera);

	init_chunks(game.lvl);
	init_background(&game);

	// init collision
	init_collisions(game.lvl);

	//init player collision
	game.lvl->player->collider->id = 0;
	game.lvl->player->collider->min = game.lvl->images[e_player]->pos;
	game.lvl->player->collider->size = game.lvl->images[e_player]->size;


	mlx_hook(game.window, KeyPress, KeyPressMask, &press_key, &game);
	mlx_hook(game.window, KeyRelease, KeyReleaseMask, &release_key, &game);
	mlx_loop_hook(game.mlx, on_update, &game.mlx);
	mlx_loop(game.mlx);

	mlx_do_key_autorepeaton(game.mlx);
	(void)argc;
	(void)argv;
	(void)game;
	return (0);
}
