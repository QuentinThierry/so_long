/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx_put_img_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/09 01:48:55 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int	get_color_at(t_pict *img, t_vector2 pos)
{
	char	*dst;

	dst = img->addr + (pos.y * img->line_length + pos.x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)(dst));
}

void	change_color(t_pict *img, t_vector2 pos, unsigned int color)
{
	char	*dst;

	dst = img->addr + (pos.y * img->line_length + pos.x * (img->bits_per_pixel / 8));
	*(unsigned int*)(dst) = color;
}

unsigned int	get_blended_color(t_mlx *mlx, t_vector2 pos)
{
	unsigned int	color_depth_back;
	unsigned int	red_back;
	unsigned int	green_back;
	unsigned int	blue_back;
	unsigned int	color_depth_front;
	unsigned int	red_front;
	unsigned int	green_front;
	unsigned int	blue_front;
	unsigned int	res;
	double			res_alpha;
	unsigned int	res_red;
	unsigned int	res_green;
	unsigned int	res_blue;
	double			alpha_back;
	double			alpha_front;

	color_depth_back = get_color_at(mlx->imgs[e_background], pos);
	alpha_back = ((double)(color_depth_back >> 24) / (double)0xff);
	red_back = (color_depth_back & 0xFF0000) >> 16;
	green_back = (color_depth_back & 0xFF00) >> 8;
	blue_back = (color_depth_back & 0xFF);

	color_depth_front = get_color_at(mlx->imgs[e_tile], pos);
	alpha_front = ((double)(color_depth_front >> 24) / (double)0xff);
	red_front = (color_depth_front & 0xFF0000) >> 16;
	green_front = (color_depth_front & 0xFF00) >> 8;
	blue_front = (color_depth_front & 0xFF);

	res_red = alpha_front * (double)red_front + (1 - alpha_front) * alpha_back * red_back;
	res_green = alpha_front * (double)green_front + (1 - alpha_front) * alpha_back * green_back;
	res_blue = alpha_front * (double)blue_front + (1 - alpha_front) * alpha_back * blue_back;
	res_alpha = alpha_front + (1 - alpha_front) * alpha_back;

	res = (unsigned int)(res_alpha * 0xff) << 24;
	res += res_red << 16;
	res += res_green << 8;
	res += res_blue;

	return (res);
}

// frontAlph * colorFront + (1 - frontAlph) * alphaBack * colorBack
// alpha = frontAlph + (1 - frontAlph) * backAlph

void	apply_transparency_on_image(t_mlx *mlx)
{
	int				i;
	int				j;
	int				alpha;
	char			*dst;
	unsigned int	color;
	t_pict			*img;

	img = mlx->imgs[e_tile]->img;
	i = 0;
	while (i < ((t_img *)img)->image->width)
	{
		j = 0;
		while (j < ((t_img *)img)->image->height)
		{
			if (get_color_at(mlx->imgs[e_tile], vector(i, j)) >> 24 != 0)
			{
				color = get_blended_color(mlx, vector(i, j));
				change_color(mlx->imgs[e_background], vector(i, j), color);
			}
			j++;
		}
		i++;
	}

}

