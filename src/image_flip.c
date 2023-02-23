/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_flip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:06:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/23 17:45:59 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <strings.h>

static inline unsigned int	*_get_address_at(t_sprite *sprite, int x, int y)
{
	return ((unsigned int *)(sprite->img_ptr->data + (y * sprite->line_length)
		+ (x * sprite->opp)));
}

static inline unsigned int	*_get_addr_at(char *data, int x, int y, int line_length)
{
	return ((unsigned int *)(data + (y * line_length * 4)
		+ (x * 4)));
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

void	_swap_pixels(t_sprite *sprite, t_vector2 pos1, t_vector2 pos2)
{
	unsigned int	*src;
	unsigned int	*dst;
	unsigned int	tmp;

	src = _get_address_at(sprite, pos1.x, pos1.y);
	dst = _get_address_at(sprite, pos2.x, pos2.y);
	tmp = *dst;
	*dst = *src;
	*src = tmp;
}

void	rotate_image(t_sprite *sprite, int angle)
{
	int		x;
	int		y;
	int		newx;
	int		newy;
	int		center_x;
	int		center_y;
	double	theta;

	theta = angle * 3.1415926F / 180;
	center_x = sprite->size.x / 2;
	center_y = sprite->size.y / 2;

	char *cpy = malloc(4 * sprite->size.x * sprite->size.y);

	memcpy(cpy, sprite->img_ptr->data, 4 * sprite->size.x * sprite->size.y);
	bzero(sprite->img_ptr->data, 4 * sprite->size.x * sprite->size.y);
	//printf("")
	y = 0;
	while (y < sprite->size.y)
	{
		x = 0;
		while (x < sprite->size.x)
		{
			newx = (x - center_x) * cosf(theta) - (y - center_y) * sinf(theta) + center_x;
			newy = (x - center_x) * sinf(theta) + (y - center_y) * cosf(theta) + center_y;
			if (!(newx < 0 || newx > sprite->size.x || newy < 0 || newy > sprite->size.y))
			{
				printf("%d->%d %d->%d\n", y, newx, x, newy);
				*_get_address_at(sprite, newx / 2, newy / 2) =
				*_get_addr_at(cpy, x, y, sprite->size.x);
			}
			
			// _swap_pixels(sprite, (t_vector2){newx, newy}, (t_vector2){y, x});
			x++;
		}
		y++;
	}
	// x = 10;
	// y = 10;
	// *_get_address_at(sprite, x, y) = RED;
	// newx = ((x - center_x) * cosf(theta) - (y - center_y) * sinf(theta)) + center_x;
	// newy = ((x - center_x) * sinf(theta) + (y - center_y) * cosf(theta)) + center_y;
	// *_get_address_at(sprite, newx, newy) = GREEN;

	// printf("%d->%d %d->%d\n", x, newx, y, newy);
}