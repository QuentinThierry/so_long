/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/11 03:18:31 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_pict *pict, int x, int y, int color)
{
	char	*dst;

	dst = pict->addr + (y * pict->line_length + x * pict->oct_per_pixel);
	*(unsigned int*)dst = color;
}

void	exec_on_w(t_mlx *mlx)
{
	mlx->player->pos.y--;
	//printf("W\n");
}

void	exec_on_a(t_mlx *mlx)
{
	mlx->player->pos.x--;
	//printf("A\n");
}

void	exec_on_s(t_mlx *mlx)
{
	mlx->player->pos.y++;
	//printf("S\n");
}

void	exec_on_d(t_mlx *mlx)
{
	mlx->player->pos.x++;
	//printf("D\n");
}

void	exec_on_e(t_mlx *mlx)
{
	//printf("Avant : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
	rotate_player(mlx->player, 1);
	//printf("Apres : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
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
			//move_pixel(mlx->imgs[e_lplayer]->img, vector(i, j), vector(10,10));
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

void	draw_to_chunk(t_canvas *canvas, int chunk, t_pict *src)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < canvas->chunks[chunk].size_y)
	{
		dst = canvas->chunks[chunk].addr +
			y * canvas->nl_offset;
		ft_memcpy(dst, src->addr, (canvas->chunks[chunk].size_x)
			* canvas->pict->oct_per_pixel);
		y++;
	}
}

int	find_chunk(t_canvas *canvas, int x, int y)
{
	int	chunk;

	chunk = (y / SIZE_CHUNK) * canvas->nb_chunks_x +
		x / SIZE_CHUNK;

	return (chunk);
}

int	draw_on_canvas_image(t_mlx *mlx, t_pict *pict,
						t_vector2 pos, int is_alpha_sensitive)
{
	int				width;
	int				height;
	char			*dst;
	int				x;
	int				y;

	width = pict->width;
	height = pict->height;
	// printf("w %d/h %d\n", width, height);
	// dst = mlx->canvas->addr + pos.y * mlx->canvas->line_length + pos.x * mlx->canvas->oct_per_pixel;
	if (!is_alpha_sensitive)
		ft_memcpy(mlx->canvas->pict->addr, pict->addr, height * pict->line_length + width * pict->oct_per_pixel);
	else
		blend_images(mlx->canvas->pict, pict);
	return (0);
}

int	draw_layers(t_mlx *mlx)
{
	//move_pixel(mlx->imgs[e_lbackground]->img, vector(10, 10), vector(100,100));
	//draw_on_canvas_image(mlx, mlx->layers[e_lbackground], (t_vector2){0, 0}, 0);
	//blend_images(mlx->canvas->pict, mlx->layers[e_ltile]);
	

	//find_chunk(mlx->canvas, 100, 100);
	
	//debug_calculate(mlx, mlx->layers[e_ldebug]);
	//blend_images(mlx->canvas->pict, mlx->layers[e_ldebug]);


	// draw_on_canvas_image(mlx, mlx->layers[e_ldebug], (t_vector2){0, 0}, 0);
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

	calculate_fps(&mlx->fps);
	// calculate_player(mlx);
	draw_layers(mlx);

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
	draw_rectangle(&mlx, (t_vector2){0 ,0}, (t_vector2){100, 100}, 0xFFFF00000);
	calculate_background(&mlx);
	
	//mlx_key_hook(mlx.window, handle_keys, &mlx);

	mlx_hook(mlx.window, KeyPress, KeyPressMask, &handle_keys, &mlx);
	mlx_loop_hook(mlx.mlx, on_update, &mlx.mlx);
	mlx_loop(mlx.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
