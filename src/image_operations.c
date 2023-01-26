/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:02:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/26 18:28:49 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	draw_image_on_canvas(t_canvas *canvas, t_pict *pict,
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
				+ canvas->pict->opp * pos.x;
			ft_memcpy(dst, pict->addr + pict->line_length * y,
				pict->size.x * canvas->pict->opp);
			y++;
		}
	}
	else
		blend_images(canvas->pict, pict, pos);
	return (0);
}

// clear all pixels of an image
void	clear_image(t_pict *pict)
{
	int	y;

	y = 0;
	while (y < pict->size.y)
	{
		ft_bzero(pict->addr + y * pict->size.x * pict->opp,
			pict->size.x * pict->opp);
		y++;
	}
}