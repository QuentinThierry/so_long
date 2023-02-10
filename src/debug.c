/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:50:40 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/10 21:33:51 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	debug_draw_hover_chunks(t_level *lvl)
{
	int	i;

	i = 0;
	while (i < lvl->canvas->nb_chunks.x * (lvl->canvas->nb_chunks.y))
	{
		if (lvl->canvas->chunks_to_redraw[i] == 1)
		{
			draw_image_on_image(lvl->cam->sprite,
				lvl->debug_tile_sprite,
			(t_vector2)
			{
				lvl->canvas->chunks[i].pos.x - lvl->cam->pos->x,
				lvl->canvas->chunks[i].pos.y - lvl->cam->pos->y
			}, 1);
		}
		++i;
	}
}

void	debug_calculate(t_level *lvl)
{
	debug_draw_hover_chunks(lvl);
}