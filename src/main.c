/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/09 01:49:53 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_pict *img, int x, int y, int color)
{
	char	*dst;

	//printf("%d\n"), *(unsigned int*)img->addr;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
			my_mlx_pixel_put(mlx->imgs[e_tile], pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

void	show_fps(t_mlx *mlx, t_vector2 pos, int fps)
{
	mlx_string_put(mlx->mlx, mlx->window, pos.x + mlx->offset_x,
		pos.y + mlx->offset_y, 0xFFFFFF, ft_itoa(fps));
}

int	calculate_background(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(mlx->imgs[e_background], i, j, 0xFFFF0000);
			j++;
		}
		i++;
	}
	return (0);
}

void	move_pixel(t_pict *img, t_vector2 pix_pos, t_vector2 delta)
{
	//unsigned int	color;
	//char			*dst;

	//printf("%d\n", *(unsigned int*)img->addr);
	//dst = img->addr + ((pix_pos.y + delta.y) * img->line_length
	//	+ (pix_pos.x + delta.x) * (img->bits_per_pixel / 8));
	//*(unsigned int *)dst = color;
}

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
			//move_pixel(mlx->imgs[e_player]->img, vector(i, j), vector(10,10));
			//my_mlx_pixel_put(mlx->imgs[e_player]->img, 10, 10, 0x00FF00);
			j++;
		}
		i++;
	}
	//my_mlx_pixel_put(mlx->imgs[e_player], 50, 50, 0xFF0000);
	return (0);
}

int	draw_layers(t_mlx *mlx)
{
	//draw_rectangle(mlx, vector(100, 99), vector(100, 100), 0xFF00FF00);
	//move_pixel(mlx->imgs[e_background]->img, vector(10, 10), vector(100,100));
	apply_transparency_on_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->imgs[e_background]->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->imgs[e_player]->img, mlx->player->pos.x, mlx->player->pos.y);
	//mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->imgs[e_tile]->img, 0, 0);
	//printf("Color 200, 200 : %#x\n", get_color_at(mlx->imgs[e_background], vector(200, 200)));
	return (0);
}

int	on_update(t_mlx *mlx)
{
	static unsigned int	frame = 0;
	static int			fps = 0;

	calculate_fps(&mlx->fps);
	calculate_background(mlx);
	calculate_player(mlx);
	draw_rectangle(mlx, vector(0, 0), vector(100, 100), 0x4000FF00);
	draw_layers(mlx);

	if (frame % FRAME_RATE_DRAW_SPEED == 0)
	{
		fps = mlx->fps;
		frame = 0;
	}
	show_fps(mlx, vector(FPS_POSX, FPS_POSY), fps);
	frame++;
	get_blended_color(mlx, vector(100,100));
	return (0);
}

t_mlx	init_values()
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.window = NULL;
	mlx.imgs[e_background] = malloc(sizeof(t_pict));
	mlx.imgs[e_fps] = malloc(sizeof(t_pict));
	mlx.imgs[e_player] = malloc(sizeof(t_pict));
	mlx.imgs[e_tile] = malloc(sizeof(t_pict));
	mlx.player = malloc(sizeof(t_player));
	mlx.player->pos.x = 0;
	mlx.player->pos.y = 0;
	mlx.player->rot.x = 0.0;
	mlx.player->rot.y = 0.0;
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
	mlx->imgs[e_background]->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->imgs[e_fps]->img = mlx_new_image(mlx->mlx, 100, 100);
	mlx->imgs[e_tile]->img = mlx_new_image(mlx->mlx, 100, 100);
	mlx->imgs[e_player]->img = mlx_xpm_file_to_image(mlx->mlx, "assets/abeille.xpm", &img_width, &img_height);
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

	mlx.imgs[e_background]->addr = mlx_get_data_addr(mlx.imgs[e_background]->img,
								&mlx.imgs[e_background]->bits_per_pixel,
								&mlx.imgs[e_background]->line_length,
								&mlx.imgs[e_background]->endian);
	mlx.imgs[e_fps]->addr = mlx_get_data_addr(mlx.imgs[e_fps]->img,
								&mlx.imgs[e_fps]->bits_per_pixel,
								&mlx.imgs[e_fps]->line_length,
								&mlx.imgs[e_fps]->endian);
	mlx.imgs[e_player]->addr = mlx_get_data_addr(mlx.imgs[e_player]->img,
								&mlx.imgs[e_player]->bits_per_pixel,
								&mlx.imgs[e_player]->line_length,
								&mlx.imgs[e_player]->endian);
	mlx.imgs[e_tile]->addr = mlx_get_data_addr(mlx.imgs[e_tile]->img,
								&mlx.imgs[e_tile]->bits_per_pixel,
								&mlx.imgs[e_tile]->line_length,
								&mlx.imgs[e_tile]->endian);

	//mlx_key_hook(mlx.window, handle_keys, &mlx);

	mlx_hook(mlx.window, KeyPress, KeyPressMask, &handle_keys, &mlx);
	mlx_loop_hook(mlx.mlx, on_update, &mlx.mlx);

	mlx_loop(mlx.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
