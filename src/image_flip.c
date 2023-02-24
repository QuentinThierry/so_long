/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_flip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:06:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/24 01:54:37 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static inline unsigned int	*_get_address_at(t_sprite *sprite, int x, int y)
{
	return ((unsigned int *)(sprite->img_ptr->data + (y * sprite->line_length)
		+ (x * sprite->opp)));
}

void	flip_image_y(t_sprite *sprite)
{
	int				x;
	int				y;
	int				size_x;
	int				size_y;
	unsigned int	tmp;

	x = 0;
	y = 0;
	size_x = sprite->size.x;
	size_y = sprite->size.y;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x / 2)
		{
			tmp = *(_get_address_at(sprite, x, y));
			*(_get_address_at(sprite, x, y)) =
				*(_get_address_at(sprite, size_x - x - 1, y));
			*(_get_address_at(sprite, size_x - x - 1, y))
				= tmp;
			++x;
		}
		++y;
	}
}
