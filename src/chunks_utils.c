/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:15:22 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/28 16:30:25 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_pict	*image_at_chunk(t_level *lvl, int chunk)
{
	if (lvl->map[chunk] == '0')
		return (lvl->images[e_ground]);
	if (lvl->map[chunk] == '1')
		return (lvl->images[e_wall]);
	if (lvl->map[chunk] == 'E')
		return (lvl->images[e_exit]);
	return (lvl->images[e_ground]);
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