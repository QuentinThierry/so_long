/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:38:12 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/13 23:50:32 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <math.h>

static void	_my_mlx_pixel_put(t_sprite *sprite, int x, int y, t_color color)
{
	char	*dst;

	dst = sprite->img_ptr->data +
		(y * sprite->line_length + x * sprite->opp);
	*(unsigned int*)dst = color.color;
}

void	draw_line(t_sprite *sprite, t_vector2 src, t_vector2 dest, t_color color)
{
	int	dist;
	int	i;
	t_vector2 coo;
	t_fvector2 norm_vec;

	norm_vec = direction_normalized(src, dest);
	// printf("%f %f\n", norm_vec.x, norm_vec
	dist = (int)distance(src, dest) + 1;
	i = 0;
	while (i < dist)
	{
		coo = (t_vector2)
		{
			src.x + i * norm_vec.x,
			src.y + i * norm_vec.y
		};
		_my_mlx_pixel_put(sprite, coo.x, coo.y, color);
		i++;
	}
}
