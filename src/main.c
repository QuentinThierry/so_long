/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/06 20:08:27 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	exec_on_w(t_mlx *mlx)
{
	mlx->offset_y--;
	printf("W\n");
}

void	exec_on_a(t_mlx *mlx)
{
	mlx->offset_x--;
	printf("A\n");
}

void	exec_on_s(t_mlx *mlx)
{
	mlx->offset_y++;
	printf("S\n");
}

void	exec_on_d(t_mlx *mlx)
{
	mlx->offset_x++;
	printf("D\n");
}

int	handle_keys(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		exec_on_w(mlx);
	if (key == KEY_A)
		exec_on_a(mlx);
	if (key == KEY_S)
		exec_on_s(mlx);
	if (key == KEY_D)
		exec_on_d(mlx);
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

t_mlx	init_values()
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.window = NULL;
	mlx.img[e_background] = malloc(sizeof(t_img));
	mlx.img[e_fps] = malloc(sizeof(t_img));
	mlx.img[e_player] = malloc(sizeof(t_img));
	mlx.fps = 0;
	mlx.offset_x = 0;
	mlx.offset_y = 0;
	return (mlx);
}

void	draw_rectangle(t_mlx *mlx, t_point pos, t_point size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			my_mlx_pixel_put(mlx->img[e_fps], pos.x + i, pos.y - j, color);
			j++;
		}
		i++;
	}
}

void	show_fps(t_mlx *mlx, t_point pos)
{
	draw_rectangle(mlx, point(FPS_POSX, FPS_POSY),
		point(FPS_WIDTH, FPS_HEIGHT), 0xFF0000);
	mlx_string_put(mlx->mlx, mlx->window, pos.x + mlx->offset_x,
		pos.y + mlx->offset_y, 0xFFFFFF, ft_itoa(mlx->fps));
}

int	draw_background(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(mlx->img[e_background], i, j, 0xFF0000);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_layers(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img[e_background]->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img[e_fps]->img, 0, 0);
	return (0);
}

int	on_update(t_mlx *mlx)
{
	static unsigned int	frame = 0;

	calculate_fps(&mlx->fps);
	if (frame % FRAME_RATE_DRAW_SPEED == 0)
	{
		show_fps(mlx, point(FPS_POSX, FPS_POSY));
		frame = 0;
	}
	draw_background(mlx);
	draw_layers(mlx);

	frame++;
	return (0);
}

int	on_start(t_mlx *mlx)
{
	*mlx = init_values();
	// if (!mlx->img)
	// 	return (1); // free all img
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Trop cool");
	mlx->img[e_background]->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->img[e_fps]->img = mlx_new_image(mlx->mlx, FPS_WIDTH, FPS_HEIGHT);
	mlx->img[e_player]->img = mlx_new_image(mlx->mlx, FPS_WIDTH, FPS_HEIGHT);


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

	mlx.img[e_background]->addr = mlx_get_data_addr(mlx.img[e_background]->img,
								&mlx.img[e_background]->bits_per_pixel,
								&mlx.img[e_background]->line_length,
								&mlx.img[e_background]->endian);
	mlx.img[e_fps]->addr = mlx_get_data_addr(mlx.img[e_fps]->img,
								&mlx.img[e_fps]->bits_per_pixel,
								&mlx.img[e_fps]->line_length,
								&mlx.img[e_fps]->endian);
	mlx.img[e_player]->addr = mlx_get_data_addr(mlx.img[e_player]->img,
								&mlx.img[e_player]->bits_per_pixel,
								&mlx.img[e_player]->line_length,
								&mlx.img[e_player]->endian);
	
	printf("test\n");
	mlx_key_hook(mlx.window, handle_keys, &mlx);
	mlx_loop_hook(mlx.mlx, on_update, &mlx.mlx);

	mlx_loop(mlx.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
