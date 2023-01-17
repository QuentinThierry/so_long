/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/17 19:59:19 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <X11/X.h>

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
	int	i;
	int	j;

	i = 0;
	while (i < size.x && i < pict->size.x)
	{
		j = 0;
		while (j < size.y && i < pict->size.y)
		{
			my_mlx_pixel_put(pict, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
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
	while (y < game->canvas->nb_chunks.y)
	{
		x = 0;
		while (x < game->canvas->nb_chunks.x)
		{
			draw_to_chunk(game->canvas, x + game->canvas->nb_chunks.x * y, game->layers[e_ltile]);
			game->canvas->chunks_to_redraw[x + game->canvas->nb_chunks.x * y] = 1;
			x++;
		}
		y++;
	}
	ft_bzero(game->canvas->chunks_to_redraw, game->canvas->nb_chunks.x * game->canvas->nb_chunks.y * sizeof(bool));
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

// crash
int	calculate_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER_SIZE_X)
	{
		j = 0;
		while (j < PLAYER_SIZE_Y)
		{
			//my_mlx_pixel_put(mlx->imgs[e_lplayer]->img, 10, 10, 0x00FF00);
			j++;
		}
		i++;
	}
	//my_mlx_pixel_put(mlx->imgs[e_lplayer], 50, 50, 0xFF0000);
	return (0);
}

int	init_chunks(t_canvas *canvas)
{
	int		x;
	int		y;
	char	*address;

	address = canvas->pict->addr;
	canvas->size.x = canvas->pict->size.x;
	canvas->size.y = canvas->pict->size.y;
	canvas->nb_chunks.x = canvas->size.x / SIZE_CHUNK + (canvas->size.x % SIZE_CHUNK != 0);
	canvas->nb_chunks.y = canvas->size.y / SIZE_CHUNK + (canvas->size.y % SIZE_CHUNK != 0);
	canvas->chunks = malloc(sizeof(t_chunk) * canvas->nb_chunks.x * canvas->nb_chunks.y);
	y = 0;
	while (y < canvas->nb_chunks.y)
	{
		x = 0;
		while (x < canvas->nb_chunks.x)
		{
			canvas->nl_offset = canvas->pict->oct_per_pixel * canvas->size.x;
			canvas->chunks[y * canvas->nb_chunks.x + x].addr = address +
				(y * SCREEN_WIDTH * SIZE_CHUNK * canvas->pict->oct_per_pixel) +
				(SIZE_CHUNK * x * canvas->pict->oct_per_pixel);
			if (x == canvas->nb_chunks.x - 1 && canvas->size.x % SIZE_CHUNK != 0)
				canvas->chunks[y * canvas->nb_chunks.x + x].size_x = (canvas->size.x % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks.x + x].size_x = SIZE_CHUNK;
			if (y == canvas->nb_chunks.y - 1 && (canvas->size.y % SIZE_CHUNK) != 0)
				canvas->chunks[y * canvas->nb_chunks.x + x].size_y = (canvas->size.y % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks.x + x].size_y = SIZE_CHUNK;
			canvas->chunks[y * canvas->nb_chunks.x + x].pos = (t_vector2){
				x * SIZE_CHUNK, y * SIZE_CHUNK};
			x++;
		}
		y++;
	}
	canvas->chunks_to_redraw = malloc(sizeof(bool) * canvas->nb_chunks.x * canvas->nb_chunks.y);
	ft_bzero(canvas->chunks_to_redraw, canvas->nb_chunks.x * canvas->nb_chunks.y);
	return (0);
}

void	draw_to_chunk(t_canvas *canvas, int chunk, t_pict *src)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < canvas->chunks[chunk].size_y)
	{
		dst = canvas->chunks[chunk].addr +
			y * canvas->nl_offset;
		ft_memcpy(dst, src->addr, ((canvas->chunks[chunk].size_x))
			* canvas->pict->oct_per_pixel);
		y++;
	}
}

void	recalculate_chunks(t_game *game)
{
	int	nb_chunks;
	int	i;

	i = 0;
	nb_chunks = game->canvas->nb_chunks.x * game->canvas->nb_chunks.y;
	while (i < nb_chunks)
	{
		if (game->canvas->chunks_to_redraw[i])
			draw_to_chunk(game->canvas, i, game->layers[e_ltile]);
		i++;
	}
}

void	find_chunk_under(t_canvas *canvas, t_pict *pict)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	x = pict->origin.x / SIZE_CHUNK;
	y = pict->origin.y / SIZE_CHUNK;
	end_x = (pict->origin.x + pict->size.x) / SIZE_CHUNK;
	end_y = (pict->origin.y + pict->size.y) / SIZE_CHUNK;
	while (x <= end_x)
	{
		y = pict->origin.y / SIZE_CHUNK;
		while (y <= end_y)
		{
			canvas->chunks_to_redraw[
				y * canvas->nb_chunks.x + x
				] = 1;
			++y;
		}
		++x;
	}
}

int	draw_on_canvas_image(t_canvas *canvas, t_pict *pict,
						t_vector2 pos, int is_alpha_sensitive)
{
	char	*dst;
	int		y;

	y = 0;
	if (!is_alpha_sensitive)
	{
		while (y < pict->size.y)
		{
			dst = canvas->chunks[0].addr +
				(y + pos.y) * canvas->nl_offset + canvas->pict->oct_per_pixel * pos.x;
			ft_memcpy(dst, pict->addr + pict->line_length * y, pict->size.x
				* canvas->pict->oct_per_pixel);
			y++;
		}
	}
	else
		blend_images(canvas->pict, pict, pos);
	return (0);
}

int	draw_layers(t_game *game)
{
	recalculate_chunks(game);
	
	debug_calculate(game, game->layers[e_ldebug]);

	draw_on_canvas_image(game->canvas, game->layers[e_lplayer], (t_vector2){game->player->pos->x, game->player->pos->y}, 1);

	mlx_put_image_to_window(game->mlx, game->window, game->canvas->pict->img, 0, 0);

	ft_bzero(game->canvas->chunks_to_redraw, game->canvas->nb_chunks.x * game->canvas->nb_chunks.y * sizeof(bool));

	return (0);
}

int	on_update(t_game *game)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	move_player(game);
	draw_layers(game);

	calculate_fps(&game->fps, &game->elapsed);
	// calculate_player(game);

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
	game.canvas = malloc(sizeof(t_canvas));
	game.canvas->pict = malloc(sizeof(t_pict));
	game.layers[e_lbackground] = malloc(sizeof(t_pict));
	game.layers[e_lfps] = malloc(sizeof(t_pict));
	game.layers[e_lplayer] = malloc(sizeof(t_pict));
	game.layers[e_ltile] = malloc(sizeof(t_pict));
	game.layers[e_ldebug] = malloc(sizeof(t_pict));
	game.player = malloc(sizeof(t_player));
	game.player->pos = &game.layers[e_lplayer]->origin;
	game.player->exact_pos = (t_fvector2){0., 0.};
	game.player->dir.x = 0;
	game.player->dir.y = 0;
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
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Trop cool");
	game->canvas->pict->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->layers[e_lbackground]->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->layers[e_lfps]->img = mlx_new_image(game->mlx, 100, 100);
	game->layers[e_ltile]->img = mlx_new_image(game->mlx, SIZE_CHUNK, SIZE_CHUNK);
	game->layers[e_ldebug]->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->layers[e_lplayer]->img = mlx_xpm_file_to_image(game->mlx, "assets/abeille.xpm", &img_width, &img_height);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_game	game;

	if(on_start(&game))
		return (1);
	bettermlx_get_data_addr(game.canvas->pict);
	init_chunks(game.canvas);
	bettermlx_get_data_addr(game.layers[e_lfps]);
	bettermlx_get_data_addr(game.layers[e_lbackground]);
	bettermlx_get_data_addr(game.layers[e_lplayer]);
	bettermlx_get_data_addr(game.layers[e_ltile]);
	bettermlx_get_data_addr(game.layers[e_ldebug]);
	draw_rectangle(game.layers[e_ltile], (t_vector2){0 ,0}, (t_vector2){SIZE_CHUNK, SIZE_CHUNK}, 0xFF7F0000);
	calculate_background(&game);

	mlx_hook(game.window, KeyPress, KeyPressMask, &press_key, &game);
	mlx_hook(game.window, KeyRelease, KeyReleaseMask, &release_key, &game);
	mlx_loop_hook(game.mlx, on_update, &game.mlx);
	mlx_loop(game.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
