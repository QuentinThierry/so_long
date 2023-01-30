/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:02:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 18:33:19 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	draw_image_on_canvas(t_canvas *canvas, t_sprite *pict,
						t_vector2 pos, int is_alpha_sensitive)
{
	char	*dst;
	int		y;

	y = 0;
	if (!is_alpha_sensitive)
	{
		while (y < pict->size.y)
		{
			dst = canvas->chunks[0].addr + (y + pos.y) * canvas->nl_offset
				+ canvas->sprite->opp * pos.x;
			ft_memcpy(dst, pict->var[0]->addr + pict->line_length * y,
				pict->size.x * canvas->sprite->opp);
			y++;
		}
	}
	else
		blend_images(canvas->sprite, pict, pos);
	return (0);
}

// clear all pixels of an image
void	clear_image(t_sprite *pict)
{
	int	y;

	y = 0;
	while (y < pict->size.y)
	{
		ft_bzero(pict->var[0]->addr + y * pict->size.x * pict->opp,
			pict->size.x * pict->opp);
		y++;
	}
}