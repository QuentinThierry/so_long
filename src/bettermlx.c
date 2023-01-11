/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/11 03:03:04 by qthierry         ###   ########.fr       */
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

static u_color	get_blended_color(u_color c_back, u_color c_front)
{
	u_color	res;
	float	alpha_back;
	float	alpha_front;
	float	res_alpha;

	alpha_back = (c_back.alpha * 0.003921F);
	alpha_front = (c_front.alpha * 0.003921F);

	res.red = alpha_front * (float)c_front.red + (1.F - alpha_front) * alpha_back * (float)c_back.red;
	res.green = alpha_front * (float)c_front.green + (1.F - alpha_front) * alpha_back * (float)c_back.green;
	res.blue = alpha_front * (float)c_front.blue + (1.F - alpha_front) * alpha_back * (float)c_back.blue;
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
			c_front = (u_color)get_color_at(front, (t_vector2){i, j});
			if (c_front.alpha != 0)
			{
				c_back = (u_color)get_color_at(back, (t_vector2){i, j});
				c_back = get_blended_color(c_back, c_front);
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