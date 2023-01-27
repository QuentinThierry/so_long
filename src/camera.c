/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/27 20:03:03 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// draw on screen only a part of the canvas

void	render_camera(t_level *lvl, t_vector2 origin)
{
	int	y;
	int	xsize;
	int	deltax;
	int	opp;
	int camera_size;

	opp = lvl->camera->opp;
	camera_size = lvl->camera->size.x * opp;
	y = 0;
	deltax = 0;
	xsize = lvl->camera->size.x;
	if (origin.x + lvl->camera->size.x > lvl->canvas->size.x)
		xsize -= origin.x + lvl->camera->size.x - lvl->canvas->size.x;
	if (origin.x < 0)
		deltax = -origin.x * lvl->camera->opp;
	while (y < lvl->camera->size.y)
	{
		if (y > lvl->canvas->origin.y + lvl->canvas->size.y || (y + origin.y) < 0)
		{
			ft_memcpy(lvl->camera->addr + 
				(y * camera_size),
				lvl->images[e_background]->addr +
				(y * lvl->images[e_background]->size.x * lvl->camera->opp),
				camera_size);
		}
		else
		{
			ft_memcpy(lvl->camera->addr + deltax +
				(y * camera_size),
				lvl->canvas->pict->addr +
				((y + origin.y) * lvl->canvas->size.x * lvl->camera->opp)
				+ origin.x * lvl->camera->opp + deltax,
				xsize * lvl->camera->opp - deltax);
		}
		y++;
	}
	y = 0;
	if (origin.x < 0)
	{
		while (y < lvl->camera->size.y)
		{
			ft_memcpy(lvl->camera->addr + 
				(y * camera_size),
				lvl->images[e_background]->addr +
				(y * lvl->images[e_background]->size.x * lvl->camera->opp),
				-origin.x * lvl->camera->opp);
			y++;
		}
	}
	y = 0;
	if (origin.x + lvl->camera->size.x > lvl->canvas->size.x)
	{
		while (y < lvl->camera->size.y)
		{
			ft_memcpy(lvl->camera->addr + 
				(y * camera_size) + 
				(lvl->camera->size.x - (origin.x + lvl->camera->size.x - lvl->canvas->size.x)) * lvl->camera->opp,
				lvl->images[e_background]->addr +
				(y * lvl->images[e_background]->size.x * lvl->camera->opp) +
				(lvl->images[e_background]->size.x - (origin.x + lvl->camera->size.x - lvl->canvas->size.x)) * lvl->camera->opp,
				(origin.x + lvl->camera->size.x - lvl->canvas->size.x) * lvl->camera->opp);
			y++;
		}
	}

}
