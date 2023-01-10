/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/10 20:08:00 by qthierry         ###   ########.fr       */
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

u_color	get_blended_color(u_color c_back, u_color c_front, t_vector2 pos)
{
	u_color	res;
	double	alpha_back;
	double	alpha_front;
	double	res_alpha;

	alpha_back = ((double)c_back.alpha / (double)0xff);
	alpha_front = ((double)c_front.alpha / (double)0xff);

	res.red = alpha_front * (double)c_front.red + (1 - alpha_front) * alpha_back * c_back.red;
	res.green = alpha_front * (double)c_front.green + (1 - alpha_front) * alpha_back * c_back.green;
	res.blue = alpha_front * (double)c_front.blue + (1 - alpha_front) * alpha_back * c_back.blue;
	res_alpha = alpha_front + (1 - alpha_front) * alpha_back;

	return (res);
}

// frontAlph * colorFront + (1 - frontAlph) * alphaBack * colorBack
// alpha = frontAlph + (1 - frontAlph) * backAlph

void	blend_images(t_pict *back, t_pict *front)
{
	int				i;
	int				j;
	u_color			c_back;
	u_color			c_front;
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

			c_back = (u_color)get_color_at(back, (t_vector2){i, j});
			c_front = (u_color)get_color_at(front, (t_vector2){i, j});
			// printf("back : %x / front : %x\n", color_back, color_front);
			if (c_front.alpha == 0)
			{
				change_color(back, (t_vector2){i, j}, c_back.color);
			}
			else
			{
				c_back = get_blended_color(c_back, c_front, (t_vector2){i, j});
				change_color(back, (t_vector2){i, j}, c_back.color);
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