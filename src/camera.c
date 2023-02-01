/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/01 00:13:55 by qthierry         ###   ########.fr       */
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

	opp = lvl->cam->opp;
	camera_size = lvl->cam->size.x * opp;
	y = 0;
	deltax = 0;
	xsize = lvl->cam->size.x;
	if (origin.x + lvl->cam->size.x > lvl->canvas->size.x)
		xsize -= origin.x + lvl->cam->size.x - lvl->canvas->size.x;
	if (origin.x < 0)
		deltax = -origin.x * opp;
	while (y < lvl->cam->size.y)
	{
		if (y > lvl->canvas->origin.y + lvl->canvas->size.y + opp || (y + origin.y) < 0)
		{
			ft_memcpy(lvl->cam->img_ptr->data + 
				(y * camera_size),
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp),
				camera_size);
		}
		else
		{
			ft_memcpy(lvl->cam->img_ptr->data + deltax +
				(y * camera_size),
				lvl->canvas->sprite->img_ptr->data +
				((y + origin.y) * lvl->canvas->size.x * opp)
				+ origin.x * opp + deltax,
				xsize * opp - deltax);
		}
		y++;
	}
	y = 0;
	if (origin.x < 0)
	{
		while (y < lvl->cam->size.y)
		{
			ft_memcpy(lvl->cam->img_ptr->data + 
				(y * camera_size),
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp),
				-origin.x * opp);
			y++;
		}
	}
	y = 0;
	if (origin.x + lvl->cam->size.x > lvl->canvas->size.x)
	{
		while (y < lvl->cam->size.y)
		{
			ft_memcpy(lvl->cam->img_ptr->data + 
				(y * camera_size) + (lvl->cam->size.x - (origin.x + lvl->cam->size.x - lvl->canvas->size.x)) * opp,
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp) + (lvl->cam->size.x - (origin.x + lvl->cam->size.x - lvl->canvas->size.x)) * opp,
				(origin.x + lvl->cam->size.x - lvl->canvas->size.x) * opp);
			y++;
		}
	}
}
