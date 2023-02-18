/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_flip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:06:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 21:41:10 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static inline char	*_get_address_at(t_sprite *sprite, int x, int y)
{
	return (sprite->img_ptr->data + (y * sprite->line_length)
		+ (x * sprite->opp));
}

void	flip_image_y(t_sprite *pict)
{
	int				x;
	int				y;
	int				size_x;
	int				size_y;
	unsigned int	tmp;

	x = 0;
	y = 0;
	size_x = pict->size.x;
	size_y = pict->size.y;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x / 2)
		{
			tmp = *(unsigned int *)(_get_address_at(pict, x, y));
			*(unsigned int *)(_get_address_at(pict, x, y)) =
				*(unsigned int *)(_get_address_at(pict, size_x - x, y));
			*(unsigned int *)(_get_address_at(pict, size_x - x, y))
				= tmp;
			++x;
		}
		++y;
	}
}
