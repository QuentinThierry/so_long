/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:15:22 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/09 16:17:39 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_img	*image_at_chunk(t_level *lvl, int chunk)
{
	return (lvl->images[lvl->canvas->chunks[chunk].image_id]);
}

char	letter_at_chunk(t_level *lvl, int chunk)
{
	return (lvl->map[chunk]);
}

int		pos_to_chunk(t_level *lvl, int x, int y)
{
	return ((y / SIZE_CHUNK) * lvl->canvas->nb_chunks.x + (x / SIZE_CHUNK));
}

void	clear_chunks_to_redraw(t_canvas *canvas)
{
	ft_bzero(canvas->chunks_to_redraw, canvas->nb_chunks.x * canvas->nb_chunks.y * sizeof(int));
}