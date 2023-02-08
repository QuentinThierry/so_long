/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/08 20:58:54 by qthierry         ###   ########.fr       */
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

	opp = lvl->cam->sprite->opp;
	camera_size = lvl->cam->size->x * opp;
	y = 0;
	deltax = 0;
	xsize = lvl->cam->size->x;
	if (origin.x + lvl->cam->size->x > lvl->canvas->size.x)
		xsize -= origin.x + lvl->cam->size->x - lvl->canvas->size.x;
	if (origin.x < 0)
		deltax = -origin.x * opp;
	while (y < lvl->cam->size->y)
	{
		if (origin.y + y > lvl->canvas->size.y - 1 || (y + origin.y) < 0)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data + 
				(y * camera_size),
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp),
				camera_size);
		}
		else if (deltax < lvl->cam->size->x * opp && xsize >= 0)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data + deltax +
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
		while (y < lvl->cam->size->y)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data + 
				(y * camera_size),
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp),
				-origin.x * opp);
			y++;
		}
	}
	y = 0;
	if (origin.x + lvl->cam->size->x > lvl->canvas->size.x && xsize >= 0)
	{
		while (y < lvl->cam->size->y)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data + 
				(y * camera_size) + (xsize) * opp,
				lvl->background->img_ptr->data +
				(y * lvl->background->size.x * opp) + (xsize) * opp,
				(origin.x + lvl->cam->size->x - lvl->canvas->size.x) * opp);
			y++;
		}
	}
}

void	move_camera(t_game *game)
{
	double new_posx;
	double new_posy;

	if (!game->lvl->cam->dir.x && !game->lvl->cam->dir.y)
		return ;
	new_posx = game->lvl->cam->exact_pos.x +
		(double)(game->lvl->cam->dir.x) * CAM_SPEED * game->elapsed;
	game->lvl->cam->exact_pos.x = new_posx;
	game->lvl->cam->pos->x = floor(new_posx);
	new_posy = game->lvl->cam->exact_pos.y +
		(double)(game->lvl->cam->dir.y) * CAM_SPEED * game->elapsed;
	game->lvl->cam->exact_pos.y = new_posy;
	game->lvl->cam->pos->y = floor(new_posy);
}
