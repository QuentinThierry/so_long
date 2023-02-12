/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:50:40 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/12 02:39:50 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int _is_in_cam(t_camera *cam, t_chunk *chunk)
{
	if ((chunk->pos.x + chunk->size.x <= cam->pos->x + cam->size->x)
		&& (chunk->pos.x - chunk->size.x >= cam->pos->x)
		&& (chunk->pos.y + chunk->size.y <= cam->pos->y + cam->size->y)
		&& (chunk->pos.y - chunk->size.y >= cam->pos->y))
		return (1);
	return (0);
}

void	debug_draw_hover_chunks(t_level *lvl)
{
	int	i;

	i = 0;
	while (i < lvl->canvas->nb_chunks.x * (lvl->canvas->nb_chunks.y))
	{
		if (lvl->canvas->chunks_to_redraw[i] == 1 
			&& _is_in_cam(lvl->cam, &lvl->canvas->chunks[i]))
		{
			draw_image_on_image(lvl->cam->sprite,
				lvl->debug_tile_sprite,
			(t_vector2)
			{
				lvl->canvas->chunks[i].pos.x - lvl->cam->pos->x,
				lvl->canvas->chunks[i].pos.y - lvl->cam->pos->y
			}, HIGH_GRPHISM);
		}
		++i;
	}
}

void	debug_calculate(t_level *lvl)
{
	debug_draw_hover_chunks(lvl);
}