/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 22:33:59 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_chunk	init_a_chunk(t_level *lvl, int index, int x, int y)
{
	t_chunk	res;

	res.image_id = choose_image(lvl->map, index);
	lvl->canvas->nl_offset = lvl->canvas->sprite->opp * lvl->canvas->size.x;
	res.addr = lvl->canvas->sprite->img_ptr->data
		+ (y * lvl->canvas->size.x * SIZE_CHUNK * lvl->canvas->sprite->opp)
		+ (SIZE_CHUNK * x * lvl->canvas->sprite->opp);
	if (x == lvl->canvas->nb_chunks.x - 1
		&& lvl->canvas->size.x % SIZE_CHUNK != 0)
		res.size.x = (lvl->canvas->size.x % SIZE_CHUNK);
	else
		res.size.x = SIZE_CHUNK;
	if (y == lvl->canvas->nb_chunks.y - 1
		&& (lvl->canvas->size.y % SIZE_CHUNK) != 0)
		res.size.y = (lvl->canvas->size.y % SIZE_CHUNK);
	else
		res.size.y = SIZE_CHUNK;
	res.pos = (t_vector2){
		x * SIZE_CHUNK, y * SIZE_CHUNK};
	return (res);
}

int	init_chunks(t_level *lvl)
{
	int		x;
	int		y;

	lvl->canvas->size.x = lvl->canvas->sprite->size.x;
	lvl->canvas->size.y = lvl->canvas->sprite->size.y;
	lvl->canvas->nb_chunks.x = lvl->map_size.x;
	lvl->canvas->nb_chunks.y = lvl->map_size.y;
	lvl->canvas->chunks = ft_calloc(sizeof(t_chunk),
			lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y);
	y = 0;
	while (y < lvl->canvas->nb_chunks.y)
	{
		x = 0;
		while (x < lvl->canvas->nb_chunks.x)
		{
			lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x]
				= init_a_chunk(lvl, y * lvl->canvas->nb_chunks.x + x, x, y);
			x++;
		}
		y++;
	}
	lvl->canvas->chunks_to_redraw = ft_calloc(sizeof(int),
			lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y);
	return (0);
}

void	draw_to_chunk(t_canvas *canvas, int chunk, t_img *src)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < canvas->chunks[chunk].size.y)
	{
		dst = canvas->chunks[chunk].addr
			+ y * canvas->nl_offset;
		ft_memcpy(dst, src->data
			+ src->size_line * y, (canvas->chunks[chunk].size.x)
			* canvas->sprite->opp);
		y++;
	}
}

void	recalculate_chunks(t_level *lvl)
{
	int	nb_chunks;
	int	i;

	i = 0;
	nb_chunks = lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y;
	while (i < nb_chunks)
	{
		if (lvl->canvas->chunks_to_redraw[i])
			draw_to_chunk(lvl->canvas, i, image_at_chunk(lvl, i));
		i++;
	}
}

void	find_chunk_under(t_canvas *canvas, t_sprite *pict)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = pict->pos.y / SIZE_CHUNK;
	end_x = (pict->pos.x + pict->size.x) / SIZE_CHUNK;
	end_y = (pict->pos.y + pict->size.y) / SIZE_CHUNK;
	while (y <= end_y)
	{
		x = pict->pos.x / SIZE_CHUNK;
		while (x <= end_x)
		{
			canvas->chunks_to_redraw[
				y * canvas->nb_chunks.x + x] = 1;
			++x;
		}
		++y;
	}
}
