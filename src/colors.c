/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:50 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 02:11:39 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static unsigned int	_get_color_at(t_sprite *sprite, t_vector2 pos)
{
	char	*dst;

	dst = sprite->img_ptr->data
		+ (pos.y * sprite->line_length + pos.x * sprite->opp);
	return (*(unsigned int *)(dst));
}

static t_color	_get_blended_color(t_color c_back, t_color c_front)
{
	t_color	res;
	float	alpha_back;
	float	alpha_front;

	alpha_back = (c_back.alpha * 0.003921F);
	alpha_front = (c_front.alpha * 0.003921F);
	res.red = alpha_front * (float)c_front.red
		+ (1.F - alpha_front) * alpha_back * (float)c_back.red;
	res.green = alpha_front * (float)c_front.green
		+ (1.F - alpha_front) * alpha_back * (float)c_back.green;
	res.blue = alpha_front * (float)c_front.blue
		+ (1.F - alpha_front) * alpha_back * (float)c_back.blue;
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
		my_mlx_pixel_put(back, xy, c_front.color);
	else if (c_front.alpha != 0)
	{
		c_back = (t_color)_get_color_at(back, xy);
		c_back = _get_blended_color(c_back, c_front);
		my_mlx_pixel_put(back, xy, c_back.color);
	}
}

static t_vector2	_get_dimensions(t_sprite *back, t_sprite *front,
			t_vector2 *pos)
{
	t_vector2	dim;

	dim.x = fmin(back->size.x, front->size.x);
	dim.y = fmin(back->size.y, front->size.y);
	if (pos->x + dim.x > back->size.x)
		dim.x -= pos->x + dim.x - back->size.x;
	if (pos->x < front->pos.x)
	{
		dim.x += pos->x;
		pos->x = 0;
	}
	if (pos->y + dim.y > back->size.y)
		dim.y -= pos->y + dim.y - back->size.y;
	if (pos->y < 0)
	{
		dim.y += pos->y;
		pos->y = 0;
	}
	dim.y += pos->y;
	dim.x += pos->x;
	return (dim);
}

void	blend_image_to_image(t_sprite *back, t_sprite *front,
			t_vector2 pos)
{
	int				y;
	int				x;
	t_vector2		dim;

	dim = _get_dimensions(back, front, &pos);
	y = pos.y;
	while (y < dim.y)
	{
		x = pos.x;
		while (x < dim.x)
		{
			
			apply_blend(back, front, pos, (t_vector2){x, y});
			++x;
		}
		++y;
	}
}
