/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/05 02:53:06 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


int	print_key(int key)
{
	printf("coucou %d\n", key);
	return (0);
}

void	calculate_fps(int *fps)
{
	static struct timeval	prev_time = {0, 0};
	struct timeval			tmp;
	double					elapsed;
	
	gettimeofday(&tmp, NULL);
	elapsed = (((double)(tmp.tv_usec - prev_time.tv_usec) / 1000000));
	elapsed += tmp.tv_sec - prev_time.tv_sec;
	*fps = (int)(1.0 / elapsed);
	prev_time = tmp;
}

t_mlx	init_values()
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.window = NULL;
	mlx.fps = 0;
	return (mlx);
}

void	draw_rectangle(t_mlx *mlx, t_point pos, t_point size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.x + 100)
	{
		j = 0;
		while (j < size.y + 100)
		{
			mlx_pixel_put(mlx->mlx, mlx->window, pos.x + i, pos.y - j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	show_fps(t_mlx *mlx, t_point pos)
{
	draw_rectangle(mlx, point(FPS_POSX, FPS_POSY),
		point(FPS_WIDTH, FPS_HEIGHT));
	mlx_string_put(mlx->mlx, mlx->window, pos.x,
		pos.y, 0xFFFFFF, ft_itoa(mlx->fps));
}

int	on_update(t_mlx *mlx)
{
	static unsigned int	frame = 0;

	calculate_fps(&mlx->fps);
	if (frame % FRAME_RATE_DRAW_SPEED == 0)
		show_fps(mlx, point(FPS_POSX, FPS_POSY));
	frame++;
	return (0);
}

void	on_start(t_mlx *mlx)
{
	*mlx = init_values();
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 500, 500, "Trop cool");
}

int main(int argc, char const *argv[])
{
	t_mlx	mlx;
	//int		i;
	//int		j;

	//i = 100;
	//j = 100;
	on_start(&mlx);
	printf("test\n");
	//mlx_put_image_to_window(mlx, mlx_window, NULL, 0, 0);

	mlx_key_hook(mlx.window, print_key, NULL);
	mlx_loop_hook(mlx.mlx, on_update, &mlx.mlx);

	mlx_loop(mlx.mlx);

	(void)argc;
	(void)argv;
	return 0;
}
