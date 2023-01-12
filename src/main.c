/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/12 02:05:19 by qthierry         ###   ########.fr       */
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

int	handle_keys(int key, t_mlx *mlx)
{
	enum e_key_map e_key;

	e_key = get_key(key);
	//printf("chunk under player : %d (%d)\n", find_chunk(mlx->canvas, mlx->player->pos.x, mlx->player->pos.y));
	if (e_key != NB_KEYS)
		mlx->exec_on_key[e_key](mlx);
	return (0);
}

void	calculate_fps(int *fps)
{
	static struct timeval	prev_time = {0, 0};
	struct timeval			tmp;
	double					elapsed;
	
	gettimeofday(&tmp, NULL);
	elapsed = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC));
	elapsed += tmp.tv_sec - prev_time.tv_sec;
	*fps = (int)(1.0 / elapsed);
	prev_time = tmp;
}

void	draw_rectangle(t_mlx *mlx, t_vector2 pos, t_vector2 size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			my_mlx_pixel_put(mlx->layers[e_ltile], pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

void	show_fps(t_mlx *mlx, t_vector2 pos, int fps)
{
	mlx_string_put(mlx->mlx, mlx->window, pos.x + mlx->offset_x,
		pos.y + mlx->offset_y, 0xFFFFFFFF, ft_itoa(fps));
}

int	calculate_background(t_mlx *mlx)
{
	int	x;
	int	y;

	//x = 0;
	//while (x < SCREEN_WIDTH)
	//{
	//	y = 0;
	//	while (y < SCREEN_HEIGHT)
	//	{
	//		my_mlx_pixel_put(mlx->layers[e_lbackground], x, y, 0xFF5F0000);
	//		y++;
	//	}
	//	x++;
	//}

	y = 0;
	while (y < mlx->canvas->nb_chunks_y)
	{
		x = 0;
		while (x < mlx->canvas->nb_chunks_x)
		{
			//printf("y : %d x : %d\n", y, x);
			draw_to_chunk(mlx->canvas, x + mlx->canvas->nb_chunks_x * y, mlx->layers[e_ltile]);
			x++;
		}
		y++;
	}
	return (0);
}

void	move_pixel(t_pict *pict, t_vector2 delta)
{
	int				x;
	int				y;

	y = 0;
	while (y < pict->height)
	{
		x = 0;
		while (x < pict->width)
		{
			if (!(x + delta.x > pict->width && y + delta.y > pict->height))
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
int	calculate_player(t_mlx *mlx)
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
	canvas->width = canvas->pict->width;
	canvas->height = canvas->pict->height;
	canvas->nb_chunks_x = canvas->width / SIZE_CHUNK + (canvas->width % SIZE_CHUNK != 0);
	canvas->nb_chunks_y = canvas->height / SIZE_CHUNK + (canvas->height % SIZE_CHUNK != 0);
	canvas->chunks = malloc(sizeof(t_chunk) * canvas->nb_chunks_x * canvas->nb_chunks_y);
	y = 0;
	while (y < canvas->nb_chunks_y)
	{
		x = 0;
		while (x < canvas->nb_chunks_x)
		{
			canvas->nl_offset = canvas->pict->oct_per_pixel * canvas->width;
			canvas->chunks[y * canvas->nb_chunks_x + x].addr = address +
				(y * SCREEN_WIDTH * SIZE_CHUNK * canvas->pict->oct_per_pixel) +
				(SIZE_CHUNK * x * canvas->pict->oct_per_pixel);
			if (x == canvas->nb_chunks_x - 1 && canvas->width % SIZE_CHUNK != 0)
				canvas->chunks[y * canvas->nb_chunks_x + x].size_x = (canvas->width % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks_x + x].size_x = SIZE_CHUNK;
			if (y == canvas->nb_chunks_y - 1 && (canvas->height % SIZE_CHUNK) != 0)
				canvas->chunks[y * canvas->nb_chunks_x + x].size_y = (canvas->height % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks_x + x].size_y = SIZE_CHUNK;
			x++;
		}
		y++;
	}
	canvas->chunks_to_redraw = malloc(sizeof(bool) * canvas->nb_chunks_x * canvas->nb_chunks_y);
	ft_bzero(canvas->chunks_to_redraw, canvas->nb_chunks_x * canvas->nb_chunks_y);
	return (0);
}

void	debug_draw_chunks(t_canvas *canvas, t_pict *debug_image)
{
	int	x;
	int	y;

	y = 0;
	while (y < canvas->nb_chunks_y)
	{
		x = 0;
		while (x < canvas->nb_chunks_x)
		{
			*(unsigned int *)(debug_image->addr +
				canvas->nl_offset * y * SIZE_CHUNK +
				canvas->pict->oct_per_pixel *
				(canvas->chunks[y * canvas->nb_chunks_x + x].size_x) * x)
				= GREEN;
			x++;
		}
		y++;
	}
}

void	debug_calculate(t_mlx *mlx, t_pict *debug_image)
{
	debug_draw_chunks(mlx->canvas, debug_image);
}

void	refresh_chunks(t_mlx *mlx)
{
	int	nb_chunks;
	int	i;

	i = 0;
	nb_chunks = mlx->canvas->nb_chunks_x * mlx->canvas->nb_chunks_y;
	while (i < nb_chunks)
	{
		if (mlx->canvas->chunks_to_redraw[i])
			draw_to_chunk(mlx->canvas, i, mlx->layers[e_ltile]);
		i++;
	}
	ft_bzero(mlx->canvas->chunks_to_redraw, nb_chunks * sizeof(bool));
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

void	find_chunk(t_canvas *canvas, int x, int y)
{
	canvas->chunks_to_redraw[
		((y - 1) / SIZE_CHUNK) * canvas->nb_chunks_x +
		(x - 1) / SIZE_CHUNK
		] = 1;
}

int	draw_on_canvas_image(t_canvas *canvas, t_pict *pict,
						t_vector2 pos, int is_alpha_sensitive)
{
	char			*dst;
	int				y;

	y = 0;
	if (!is_alpha_sensitive)
	{
		while (y < pict->height)
		{
			dst = canvas->chunks[0].addr +
				(y + pos.y) * canvas->nl_offset + canvas->pict->oct_per_pixel * pos.x;
			ft_memcpy(dst, pict->addr + pict->line_length * y, pict->width
				* canvas->pict->oct_per_pixel);
			y++;
		}
	}
	else
		blend_images(canvas->pict, pict);
	return (0);
}

int	draw_layers(t_mlx *mlx)
{
	//move_pixel(mlx->imgs[e_lbackground]->img, vector(10, 10), vector(100,100));
	//draw_on_canvas_image(mlx, mlx->layers[e_lbackground], (t_vector2){0, 0}, 0);
	//blend_images(mlx->canvas->pict, mlx->layers[e_ltile]);
	
	refresh_chunks(mlx);
	draw_on_canvas_image(mlx->canvas, mlx->layers[e_lplayer], (t_vector2){mlx->player->pos.x, mlx->player->pos.y}, 0);
	
	// debug_calculate(mlx, mlx->layers[e_ldebug]);
	// blend_images(mlx->canvas->pict, mlx->layers[e_ldebug]);
	//ft_bzero(mlx->canvas->pict->addr, mlx->canvas->height * mlx->canvas->width * mlx->canvas->pict->oct_per_pixel);

	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->canvas->pict->img, 0, 0);

	// mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->layers[e_ldebug]->img, 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->layers[e_lplayer]->img, mlx->player->pos.x, mlx->player->pos.y);
	// mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->layers[e_ltile]->img, 0, 0);
	//printf("Color 200, 200 : %#x\n", get_color_at(mlx->imgs[e_lbackground], vector(200, 200)));
	return (0);
}

int	on_update(t_mlx *mlx)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	draw_layers(mlx);

	calculate_fps(&mlx->fps);
	calculate_player(mlx);

	if (frame % FRAME_RATE_DRAW_SPEED == 0)
	{
		fps = mlx->fps;
		frame = 0;
	}
	show_fps(mlx, (t_vector2){FPS_POSX, FPS_POSY}, fps);
	frame++;
	return (0);
}

t_mlx	init_values()
{
	t_mlx	mlx;
	mlx.mlx = NULL;
	mlx.window = NULL;
	mlx.canvas = malloc(sizeof(t_canvas));
	mlx.canvas->pict = malloc(sizeof(t_pict));
	mlx.layers[e_lbackground] = malloc(sizeof(t_pict));
	mlx.layers[e_lfps] = malloc(sizeof(t_pict));
	mlx.layers[e_lplayer] = malloc(sizeof(t_pict));
	mlx.layers[e_ltile] = malloc(sizeof(t_pict));
	mlx.layers[e_ldebug] = malloc(sizeof(t_pict));
	mlx.player = malloc(sizeof(t_player));
	mlx.player->pos.x = 0;
	mlx.player->pos.y = 0;
	mlx.player->rot.x = 0;
	mlx.player->rot.y = 0;
	mlx.exec_on_key[e_W] = &exec_on_w;
	mlx.exec_on_key[e_A] = &exec_on_a;
	mlx.exec_on_key[e_S] = &exec_on_s;
	mlx.exec_on_key[e_D] = &exec_on_d;
	mlx.exec_on_key[e_E] = &exec_on_e;
	mlx.exec_on_key[e_ESC] = &exec_on_w;
	mlx.fps = 0;
	mlx.offset_x = 0;
	mlx.offset_y = 0;
	return (mlx);
}

int	on_start(t_mlx *mlx)
{
	int	img_width = 200;
	int	img_height = 200;

	*mlx = init_values();
	// if (!mlx->img)
	// 	return (1); // free all img
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Trop cool");
	mlx->canvas->pict->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->layers[e_lbackground]->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->layers[e_lfps]->img = mlx_new_image(mlx->mlx, 100, 100);
	mlx->layers[e_ltile]->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->layers[e_ldebug]->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->layers[e_lplayer]->img = mlx_xpm_file_to_image(mlx->mlx, "assets/abeille.xpm", &img_width, &img_height);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_mlx	mlx;
	//int		i;
	//int		j;

	//i = 100;
	//j = 100;
	if(on_start(&mlx))
		return (1);
	bettermlx_get_data_addr(mlx.canvas->pict);
	init_chunks(mlx.canvas);
	bettermlx_get_data_addr(mlx.layers[e_lfps]);
	bettermlx_get_data_addr(mlx.layers[e_lbackground]);
	bettermlx_get_data_addr(mlx.layers[e_lplayer]);
	bettermlx_get_data_addr(mlx.layers[e_ltile]);
	bettermlx_get_data_addr(mlx.layers[e_ldebug]);
	draw_rectangle(&mlx, (t_vector2){0 ,0}, (t_vector2){0, 0}, 0xFFFF0000);
	calculate_background(&mlx);
	move_pixel(mlx.layers[e_lplayer], (t_vector2){0, 0});

	
	
	//mlx_key_hook(mlx.window, handle_keys, &mlx);

	mlx_hook(mlx.window, KeyPress, KeyPressMask, &handle_keys, &mlx);
	mlx_loop_hook(mlx.mlx, on_update, &mlx.mlx);
	mlx_loop(mlx.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
