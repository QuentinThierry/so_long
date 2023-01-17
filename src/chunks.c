/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/17 20:04:48 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_chunks(t_canvas *canvas)
{
	int		x;
	int		y;
	char	*address;

	address = canvas->pict->addr;
	canvas->size.x = canvas->pict->size.x;
	canvas->size.y = canvas->pict->size.y;
	canvas->nb_chunks.x = canvas->size.x / SIZE_CHUNK + (canvas->size.x % SIZE_CHUNK != 0);
	canvas->nb_chunks.y = canvas->size.y / SIZE_CHUNK + (canvas->size.y % SIZE_CHUNK != 0);
	canvas->chunks = malloc(sizeof(t_chunk) * canvas->nb_chunks.x * canvas->nb_chunks.y);
	y = 0;
	while (y < canvas->nb_chunks.y)
	{
		x = 0;
		while (x < canvas->nb_chunks.x)
		{
			canvas->nl_offset = canvas->pict->oct_per_pixel * canvas->size.x;
			canvas->chunks[y * canvas->nb_chunks.x + x].addr = address +
				(y * SCREEN_WIDTH * SIZE_CHUNK * canvas->pict->oct_per_pixel) +
				(SIZE_CHUNK * x * canvas->pict->oct_per_pixel);
			if (x == canvas->nb_chunks.x - 1 && canvas->size.x % SIZE_CHUNK != 0)
				canvas->chunks[y * canvas->nb_chunks.x + x].size_x = (canvas->size.x % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks.x + x].size_x = SIZE_CHUNK;
			if (y == canvas->nb_chunks.y - 1 && (canvas->size.y % SIZE_CHUNK) != 0)
				canvas->chunks[y * canvas->nb_chunks.x + x].size_y = (canvas->size.y % SIZE_CHUNK);
			else
				canvas->chunks[y * canvas->nb_chunks.x + x].size_y = SIZE_CHUNK;
			canvas->chunks[y * canvas->nb_chunks.x + x].pos = (t_vector2){
				x * SIZE_CHUNK, y * SIZE_CHUNK};
			x++;
		}
		y++;
	}
	canvas->chunks_to_redraw = malloc(sizeof(bool) * canvas->nb_chunks.x * canvas->nb_chunks.y);
	ft_bzero(canvas->chunks_to_redraw, canvas->nb_chunks.x * canvas->nb_chunks.y);
	return (0);
}

void	draw_to_chunk(t_canvas *canvas, int chunk, t_pict *src)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < canvas->chunks[chunk].size_y)
	{
		dst = canvas->chunks[chunk].addr +
			y * canvas->nl_offset;
		ft_memcpy(dst, src->addr, ((canvas->chunks[chunk].size_x))
			* canvas->pict->oct_per_pixel);
		y++;
	}
}

void	recalculate_chunks(t_game *game)
{
	int	nb_chunks;
	int	i;

	i = 0;
	nb_chunks = game->canvas->nb_chunks.x * game->canvas->nb_chunks.y;
	while (i < nb_chunks)
	{
		if (game->canvas->chunks_to_redraw[i])
			draw_to_chunk(game->canvas, i, game->layers[e_ltile]);
		i++;
	}
}

void	find_chunk_under(t_canvas *canvas, t_pict *pict)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	x = pict->origin.x / SIZE_CHUNK;
	y = pict->origin.y / SIZE_CHUNK;
	end_x = (pict->origin.x + pict->size.x) / SIZE_CHUNK;
	end_y = (pict->origin.y + pict->size.y) / SIZE_CHUNK;
	while (x <= end_x)
	{
		y = pict->origin.y / SIZE_CHUNK;
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
