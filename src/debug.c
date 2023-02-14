/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:50:40 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/13 23:54:50 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int _is_in_cam(t_camera *cam, t_chunk *chunk)
{
	if ((chunk->pos.x + chunk->size.x <= cam->pos->x + cam->size->x)
		&& (chunk->pos.x - chunk->size.x >= cam->pos->x - SIZE_CHUNK)
		&& (chunk->pos.y + chunk->size.y <= cam->pos->y + cam->size->y)
		&& (chunk->pos.y - chunk->size.y >= cam->pos->y - SIZE_CHUNK))
		return (1);
	return (0);
}

static void	_debug_draw_hover_chunks(t_level *lvl)
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

void	draw_shortest_path(t_level *lvl, int end)
{
	int	coo1x;
	int	coo1y;
	int	coo2x;
	int	coo2y;
	int	offset;

	while (lvl->path_grid[end].parent != 0)
	{
		if (_is_in_cam(lvl->cam, &lvl->canvas->chunks[end]))
		{
			offset = SIZE_CHUNK / 2;
			coo1x = lvl->canvas->chunks[end].pos.x - lvl->cam->pos->x + offset;
			coo1y = lvl->canvas->chunks[end].pos.y - lvl->cam->pos->y + offset;
			coo2x = lvl->canvas->chunks[lvl->path_grid[end].parent].pos.x
					- lvl->cam->pos->x + offset;
			coo2y = lvl->canvas->chunks[lvl->path_grid[end].parent].pos.y
					- lvl->cam->pos->y + offset;
			draw_line(lvl->cam->sprite,
			(t_vector2){coo1x, coo1y},
			(t_vector2){coo2x, coo2y},
			(t_color)RED);
		}
		end = lvl->path_grid[end].parent;
	}
}

void	debug_calculate(t_level *lvl)
{
	_debug_draw_hover_chunks(lvl);
}
