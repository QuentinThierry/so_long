/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_flip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:06:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 15:53:28 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flip_image_y(t_sprite *pict)
{
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	unsigned	tmp;

	x = 0;
	y = 0;
	size_x = pict->size.x;
	size_y = pict->size.y;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x / 2)
		{
			tmp = *(unsigned int*)(get_address_at(pict, x, y));
			*(unsigned int*)(get_address_at(pict, x, y)) = 
				*(unsigned int*)(get_address_at(pict, size_x - x, y));
				*(unsigned int*)(get_address_at(pict, size_x - x, y))
				= tmp;
			++x;
		}
		++y;
	}
}

void flip_image_x(t_sprite *pict)
{
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	unsigned	tmp;

	x = 0;
	y = 0;
	size_x = pict->size.x;
	size_y = pict->size.y;
	while (x < size_x)
	{
		y = 0;
		while (y < size_y / 2)
		{
			tmp = *(unsigned int*)(get_address_at(pict, x, y));
			*(unsigned int*)(get_address_at(pict, x, y)) = 
				*(unsigned int*)(get_address_at(pict, size_x - x, y));
				*(unsigned int*)(get_address_at(pict, size_x - x, y))
				= tmp;
			++y;
		}
		++x;
	}
}
