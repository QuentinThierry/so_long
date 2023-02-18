/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:50 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 21:06:12 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static unsigned int	_get_color_at(t_sprite *sprite, t_vector2 pos)
{
	char	*dst;

	dst = sprite->img_ptr->data +
		(pos.y * sprite->line_length + pos.x * sprite->opp);
	return (*(unsigned int*)(dst));
}

static void	_change_color(t_sprite *sprite, t_vector2 pos, unsigned int color)
{
	char	*dst;

	dst = sprite->img_ptr->data +
		(pos.y * sprite->line_length + pos.x * sprite->opp);
	*(unsigned int*)(dst) = color;
}

static t_color	_get_blended_color(t_color c_back, t_color c_front)
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

inline static void	apply_blend(t_sprite *back,
		t_sprite *front, t_vector2 pos, t_vector2 xy)
{
	t_color			c_back;
	t_color			c_front;

	c_front = (t_color)_get_color_at(front,
			(t_vector2){xy.x - pos.x, xy.y - pos.y});
	if (c_front.alpha == 0xff)
		_change_color(back, xy, c_front.color);
	else if (c_front.alpha != 0)
	{
		c_back = (t_color)_get_color_at(back, xy);
		c_back = _get_blended_color(c_back, c_front);
		_change_color(back, xy, c_back.color);
	}
}

void	blend_image_to_image(t_sprite *back, t_sprite *front,
			t_vector2 pos)
{
	int				y;
	int				x;
	int				width;
	int				height;

	width = fmin(back->size.x, front->size.x);
	height = fmin(back->size.y, front->size.y);
	if (pos.x + width > back->size.x)
		width -= pos.x + width - back->size.x;
	if (pos.x < front->pos.x)
	{
		width += pos.x;
		pos.x = 0;
	}
	if (pos.y + height > back->size.y)
		height -= pos.y + height - back->size.y;
	if (pos.y < 0)
	{
		height += pos.y;
		pos.y = 0;
	}
	y = pos.y;
	height += pos.y;
	width += pos.x;
	
	while (y < height)
	{
		x = pos.x;
		while (x < width)
		{
			apply_blend(back, front, pos, (t_vector2){x, y});
			x++;
		}
		++y;
	}
}
