/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/10 01:59:08 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int	get_color_at(t_pict *pict, t_vector2 pos)
{
	char	*dst;

	dst = pict->addr + (pos.y * pict->line_length + pos.x * pict->oct_per_pixel);
	return (*(unsigned int*)(dst));
}

void	change_color(t_pict *pict, t_vector2 pos, unsigned int color)
{
	char	*dst;

	dst = pict->addr + (pos.y * pict->line_length + pos.x * pict->oct_per_pixel);
	*(unsigned int*)(dst) = color;
}

unsigned int	get_blended_color(unsigned int color_depth_back, unsigned int color_depth_front, t_vector2 pos)
{
	unsigned int	red_back;
	unsigned int	green_back;
	unsigned int	blue_back;
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

	alpha_back = ((double)(color_depth_back >> 24) / (double)0xff);
	red_back = (color_depth_back & RED) >> 16;
	green_back = (color_depth_back & GREEN) >> 8;
	blue_back = (color_depth_back & BLUE);

	alpha_front = ((double)(color_depth_front >> 24) / (double)0xff);
	red_front = (color_depth_front & RED) >> 16;
	green_front = (color_depth_front & GREEN) >> 8;
	blue_front = (color_depth_front & BLUE);

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

void	blend_images(t_pict *back, t_pict *front)
{
	int				i;
	int				j;
	unsigned int	color_back;
	unsigned int	color_front;
	int				width;
	int				height;

	i = 0;
	width = min(back->width, front->width);
	height = min(back->height, front->height);
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			color_back = get_color_at(back, (t_vector2){i, j});
			color_front = get_color_at(front, (t_vector2){i, j});
			printf("back : %x / front : %x\n", color_back, color_front);
			if (color_front >> 24 == 0)
			{
				change_color(back, (t_vector2){i, j}, color_back);
			}
			else
			{
				color_back = get_blended_color(color_back, color_front, (t_vector2){i, j});
				change_color(back, (t_vector2){i, j}, color_back);
			}
			j++;
		}
		i++;
	}
}

void	bettermlx_get_data_addr(t_pict *pict)
{
	t_img	*img;

	img = pict->img;
	pict->addr = img->data;
	pict->oct_per_pixel = img->bpp / 8;
	pict->line_length = img->size_line;
	pict->endian = img->image->byte_order;
	pict->width = img->width;
	pict->height = img->height;
}