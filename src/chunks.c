/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/26 18:29:32 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_chunks(t_level *lvl)
{
	int		x;
	int		y;
	char	*address;

	address = lvl->canvas->pict->addr;
	lvl->canvas->size.x = lvl->canvas->pict->size.x;
	lvl->canvas->size.y = lvl->canvas->pict->size.y;
	lvl->canvas->nb_chunks.x = lvl->map_size.x;
	lvl->canvas->nb_chunks.y = lvl->map_size.y;
	lvl->canvas->chunks = malloc(sizeof(t_chunk) * lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y);
	y = 0;
	while (y < lvl->canvas->nb_chunks.y)
	{
		x = 0;
		while (x < lvl->canvas->nb_chunks.x)
		{
			lvl->canvas->nl_offset = lvl->canvas->pict->opp * lvl->canvas->size.x;
			lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].addr = address +
				(y * lvl->canvas->size.x * SIZE_CHUNK * lvl->canvas->pict->opp) +
				(SIZE_CHUNK * x * lvl->canvas->pict->opp);
			if (x == lvl->canvas->nb_chunks.x - 1 && lvl->canvas->size.x % SIZE_CHUNK != 0)
				lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].size.x = (lvl->canvas->size.x % SIZE_CHUNK);
			else
				lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].size.x = SIZE_CHUNK;
			if (y == lvl->canvas->nb_chunks.y - 1 && (lvl->canvas->size.y % SIZE_CHUNK) != 0)
				lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].size.y = (lvl->canvas->size.y % SIZE_CHUNK);
			else
				lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].size.y = SIZE_CHUNK;
			lvl->canvas->chunks[y * lvl->canvas->nb_chunks.x + x].pos = (t_vector2){
				x * SIZE_CHUNK, y * SIZE_CHUNK};
			x++;
		}
		y++;
	}
	lvl->canvas->chunks_to_redraw = malloc(sizeof(int) * lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y);
	ft_bzero(lvl->canvas->chunks_to_redraw, lvl->canvas->nb_chunks.x * lvl->canvas->nb_chunks.y);
	return (0);
}

void	draw_to_chunk(t_canvas *canvas, int chunk, t_pict *src)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < canvas->chunks[chunk].size.y)
	{
		dst = canvas->chunks[chunk].addr +
			y * canvas->nl_offset;
		ft_memcpy(dst, src->addr + src->line_length * y, (canvas->chunks[chunk].size.x) * canvas->pict->opp);
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

void	find_chunk_under(t_canvas *canvas, t_pict *pict)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	x = pict->pos.x / SIZE_CHUNK;
	y = pict->pos.y / SIZE_CHUNK;
	end_x = (pict->pos.x + pict->size.x) / SIZE_CHUNK;
	end_y = (pict->pos.y + pict->size.y) / SIZE_CHUNK;
	while (x <= end_x)
	{
		y = pict->pos.y / SIZE_CHUNK;
		while (y <= end_y)
		{
			canvas->chunks_to_redraw[
				y * canvas->nb_chunks.x + x
				] = 1;
			++y;
		}
		++x;
	}
}
