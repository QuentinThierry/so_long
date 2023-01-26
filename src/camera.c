/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/26 23:23:08 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// draw on screen only a part of the canvas

void	render_camera(t_level *lvl, t_vector2 origin)
{
	int	y;
	int	maxy;

	y = 0;
	if (origin.y < 0)
		y = -origin.y;
	maxy = lvl->camera->size.y;
	if (origin.y + lvl->camera->size.y - lvl->canvas->size.y > 0)
		maxy -= origin.y + lvl->camera->size.y - lvl->canvas->size.y;
	while (y < maxy)
	{
		ft_memcpy(lvl->camera->addr +
			(y * lvl->camera->size.x * lvl->camera->opp),
			lvl->canvas->pict->addr +
			((y + origin.y) * lvl->canvas->size.x * lvl->camera->opp)
			+ origin.x * lvl->camera->opp,
			lvl->camera->size.x * lvl->camera->opp);
		y++;
	}

}
