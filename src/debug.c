/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:50:40 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/26 18:29:41 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	debug_draw_chunks_border(t_canvas *canvas)
{
	int	x;
	int	y;

	y = 0;
	while (y < canvas->nb_chunks.y)
	{
		x = 0;
		while (x < canvas->nb_chunks.x)
		{
			*(unsigned int *)(canvas->chunks[0].addr +
				canvas->nl_offset * y * SIZE_CHUNK +
				canvas->pict->opp *
				(canvas->chunks[y * canvas->nb_chunks.x + x].size.x) * x)
				= GREEN;
			++x;
		}
		++y;
	}
}

void	debug_draw_hover_chunks(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->nb_chunks.x * (canvas->nb_chunks.y))
	{
		if (canvas->chunks_to_redraw[i] == 1)
		{
			draw_rectangle(canvas->pict,
				(t_vector2){canvas->chunks[i].pos.x, 
				canvas->chunks[i].pos.y}, (t_vector2){
				canvas->chunks[i].size.x, canvas->chunks[i].size.y},
				0x80008000);
		}
		++i;
	}
}

void	debug_calculate(t_level *lvl)
{
	debug_draw_chunks_border(lvl->canvas);
	
	debug_draw_hover_chunks(lvl->canvas);
}