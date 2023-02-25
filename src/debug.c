/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:50:40 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 02:01:24 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_debug_draw_hover_chunks(t_level *lvl)
{
	int	i;

	i = 0;
	while (i < lvl->canvas->nb_chunks.x * (lvl->canvas->nb_chunks.y))
	{
		if (lvl->canvas->chunks_to_redraw[i] == 1)
		{
			blend_image_to_image(lvl->cam->sprite,
				lvl->debug_tile_sprite,
				get_offset_for_cam(lvl->cam, lvl->canvas->chunks[i].pos));
		}
		++i;
	}
}

void	draw_shortest_path(t_level *lvl, int end)
{
	int	coo1x;
	int	coo1y;
	int	coo2x;
	int	coo2y;
	int	offset;

	while (lvl->path_grid[end].parent != 0)
	{
		offset = SIZE_CHUNK / 2;
		coo1x = lvl->canvas->chunks[end].pos.x - lvl->cam->pos->x + offset;
		coo1y = lvl->canvas->chunks[end].pos.y - lvl->cam->pos->y + offset;
		coo2x = lvl->canvas->chunks[lvl->path_grid[end].parent].pos.x
			- lvl->cam->pos->x + offset;
		coo2y = lvl->canvas->chunks[lvl->path_grid[end].parent].pos.y
			- lvl->cam->pos->y + offset;
		draw_line(lvl->cam,
			(t_vector2){coo1x, coo1y},
			(t_vector2){coo2x, coo2y},
			(t_color)((unsigned int)0x20FF0000));
		end = lvl->path_grid[end].parent;
	}
}

void	debug_calculate(t_level *lvl)
{
	_debug_draw_hover_chunks(lvl);
}
