/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:50 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:32 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int	get_color_at(t_sprite *pict, t_vector2 pos)
{
	char	*dst;

	dst = pict->var[pict->current_var]->addr +
		(pos.y * pict->line_length + pos.x * pict->opp);
	return (*(unsigned int*)(dst));
}

static void	change_color(t_sprite *pict, t_vector2 pos, unsigned int color)
{
	char	*dst;

	dst = pict->var[pict->current_var]->addr +
		(pos.y * pict->line_length + pos.x * pict->opp);
	*(unsigned int*)(dst) = color;
}

static t_color	get_blended_color(t_color c_back, t_color c_front)
{
	t_color	res;
	float	alpha_back;
	float	alpha_front;

	alpha_back = (c_back.alpha * 0.003921F);
	alpha_front = (c_front.alpha * 0.003921F);

	res.red = alpha_front * (float)c_front.red + (1.F - alpha_front) * alpha_back * (float)c_back.red;
	res.green = alpha_front * (float)c_front.green + (1.F - alpha_front) * alpha_back * (float)c_back.green;
	res.blue = alpha_front * (float)c_front.blue + (1.F - alpha_front) * alpha_back * (float)c_back.blue;
	res.alpha = alpha_front + (1 - alpha_front) * alpha_back;

	return (res);
}


void	blend_images(t_sprite *back, t_sprite *front, t_vector2 pos)
{
	int				y;
	int				x;
	t_color			c_back;
	t_color			c_front;
	int				width;
	int				height;

	y = 0;
	width = min(back->size.x, front->size.x);
	height = min(back->size.y, front->size.y);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			c_front = (t_color)get_color_at(front, (t_vector2){x, y});
			if (c_front.alpha != 0)
			{
				c_back = (t_color)get_color_at(back, (t_vector2){pos.x + x, pos.y + y});
				c_back = get_blended_color(c_back, c_front);
				change_color(back, (t_vector2){pos.x + x, pos.y + y}, c_back.color);
			}
			++x;
		}
		++y;
	}
}
