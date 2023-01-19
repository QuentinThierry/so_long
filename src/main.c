/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/19 14:34:58 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_pict *pict, int x, int y, unsigned int color)
{
	char	*dst;

	dst = pict->addr + (y * pict->line_length + x * pict->oct_per_pixel);
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
	
	gettimeofday(&tmp, NULL);
	*elapsed = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC));
	*elapsed += tmp.tv_sec - prev_time.tv_sec;
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

void	show_fps(t_game *game, t_vector2 pos, int fps)
{
	mlx_string_put(game->mlx, game->window, pos.x + game->offset_x,
		pos.y + game->offset_y, 0xFFFFFFFF, ft_itoa(fps));
}

int	calculate_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->lvl->canvas->nb_chunks.y)
	{
		x = 0;
		while (x < game->lvl->canvas->nb_chunks.x)
		{
			draw_to_chunk(game->lvl->canvas, x + game->lvl->canvas->nb_chunks.x * y, game->lvl->layers[e_ltile]);
			game->lvl->canvas->chunks_to_redraw[x + game->lvl->canvas->nb_chunks.x * y] = 1;
			x++;
		}
		y++;
	}
	ft_bzero(game->lvl->canvas->chunks_to_redraw, game->lvl->canvas->nb_chunks.x * game->lvl->canvas->nb_chunks.y * sizeof(bool));
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
								+ (x * pict->oct_per_pixel),
					pict->addr + ((y + delta.y) * pict->line_length)
								+ ((x + delta.x) * pict->oct_per_pixel),
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
	recalculate_chunks(game->lvl);
	debug_calculate(game->lvl);
	draw_image_on_canvas(game->lvl->canvas, game->lvl->layers[e_lplayer], (t_vector2){game->lvl->player->pos->x, game->lvl->player->pos->y}, 1);

	mlx_put_image_to_window(game->mlx, game->window, game->lvl->canvas->pict->img, 0, 0);
	ft_bzero(game->lvl->canvas->chunks_to_redraw, game->lvl->canvas->nb_chunks.x * game->lvl->canvas->nb_chunks.y * sizeof(bool));

	return (0);
}

int	on_update(t_game *game)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	move_player(game);
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
	game.lvl->layers[e_lbackground] = malloc(sizeof(t_pict));
	game.lvl->layers[e_lfps] = malloc(sizeof(t_pict));
	game.lvl->layers[e_lplayer] = malloc(sizeof(t_pict));
	game.lvl->layers[e_ltile] = malloc(sizeof(t_pict));
	game.lvl->layers[e_ldebug] = malloc(sizeof(t_pict));
	game.lvl->player = malloc(sizeof(t_player));
	game.lvl->player->pos = &game.lvl->layers[e_lplayer]->origin;
	game.lvl->player->exact_pos = (t_fvector2){0., 0.};
	game.lvl->player->dir.x = 0;
	game.lvl->player->dir.y = 0;
	game.elapsed = 0;
	game.press_on_key[e_W] = &press_on_w;
	game.press_on_key[e_A] = &press_on_a;
	game.press_on_key[e_S] = &press_on_s;
	game.press_on_key[e_D] = &press_on_d;
	game.press_on_key[e_E] = &press_on_e;
	game.press_on_key[e_ESC] = &press_on_w;
	game.fps = 10;
	game.offset_x = 0;
	game.offset_y = 0;
	return (game);
}

int	on_start(t_game *game)
{
	int	img_width = 200;
	int	img_height = 200;

	*game = init_values();
	// if (!mlx->img)
	// 	return (1); // free all
	game->mlx = mlx_init();
	//mlx_do_key_autorepeatoff(game->mlx);
	// XAutoRepeatOn(((t_xvar *)(game->mlx))->display);
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Trop cool");
	game->lvl->canvas->pict->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->lvl->layers[e_lbackground]->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->lvl->layers[e_lfps]->img = mlx_new_image(game->mlx, 100, 100);
	game->lvl->layers[e_ltile]->img = mlx_new_image(game->mlx, SIZE_CHUNK, SIZE_CHUNK);
	game->lvl->layers[e_ldebug]->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->lvl->layers[e_lplayer]->img = mlx_xpm_file_to_image(game->mlx, "assets/abeille.xpm", &img_width, &img_height);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_game	game;

	printf("Oui!\n");

	if(on_start(&game))
		return (1);
	game.lvl->map = NULL;
	if (argc != 2 || !parse_map(argv[1], &game.lvl->map))
	{
		write(1, "Error\nMap entry is not valid.\n", 30);
		return (1);
	}
	bettermlx_get_data_addr(game.lvl->canvas->pict);
	init_chunks(game.lvl->canvas);
	bettermlx_get_data_addr(game.lvl->layers[e_lfps]);
	bettermlx_get_data_addr(game.lvl->layers[e_lbackground]);
	bettermlx_get_data_addr(game.lvl->layers[e_lplayer]);
	bettermlx_get_data_addr(game.lvl->layers[e_ltile]);
	bettermlx_get_data_addr(game.lvl->layers[e_ldebug]);
	draw_rectangle(game.lvl->layers[e_ltile], (t_vector2){0 ,0}, (t_vector2){SIZE_CHUNK, SIZE_CHUNK}, 0xFF7F0000);
	calculate_background(&game);

	mlx_hook(game.window, KeyPress, KeyPressMask, &press_key, &game);
	mlx_hook(game.window, KeyRelease, KeyReleaseMask, &release_key, &game);
	mlx_loop_hook(game.mlx, on_update, &game.mlx);
	mlx_loop(game.mlx);

	(void)argc;
	(void)argv;
	(void)game;
	return (0);
}
