/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:02:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/10 20:30:45 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	draw_image_on_image(t_sprite *dest, t_sprite *src,
						t_vector2 pos, int is_alpha_sensitive)
{
	char	*tmp;
	int		y;

	y = 0;
	if (!is_alpha_sensitive)
	{
		while (y < src->size.y)
		{
			tmp = dest->img_ptr->data + (y + pos.y) * dest->line_length
				+ dest->opp * pos.x;
			ft_memcpy(tmp, src->img_ptr->data + src->line_length * y,
				src->size.x * dest->opp);
			y++;
		}
	}
	else
		blend_images(dest, src, pos);
	return (0);
}

void	clear_image(t_sprite *pict)
{
	int	y;

	y = 0;
	while (y < pict->size.y)
	{
		ft_bzero(pict->img_ptr->data + y * pict->size.x * pict->opp,
			pict->size.x * pict->opp);
		y++;
	}
}