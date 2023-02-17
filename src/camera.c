/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 02:47:28 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static inline void	_render_top_part(t_level *lvl,
			t_vector2 origin, int camera_size)
{
	int	y;

	y = 0;
	if (origin.x < 0)
	{
		while (y < lvl->cam->size->y)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data
				+ (y * camera_size),
				lvl->background->img_ptr->data
				+ (y * lvl->background->size.x * lvl->cam->sprite->opp),
				-origin.x * lvl->cam->sprite->opp);
			y++;
		}
	}
}

static inline void	_render_bot_part(t_level *lvl, t_vector2 origin,
			int camera_size, int xsize)
{
	int	y;

	y = 0;
	if (origin.x + lvl->cam->size->x > lvl->canvas->size.x && xsize >= 0)
	{
		while (y < lvl->cam->size->y)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data
				+ (y * camera_size) + (xsize) * lvl->cam->sprite->opp,
				lvl->background->img_ptr->data
				+ (y * lvl->background->size.x * lvl->cam->sprite->opp)
				+ (xsize) * lvl->cam->sprite->opp,
				(origin.x + lvl->cam->size->x - lvl->canvas->size.x)
				* lvl->cam->sprite->opp);
			y++;
		}
	}
}

void	_render_canvas(t_level *lvl, t_vector2 origin,
			int deltax, int xsize)
{
	int	y;
	int	opp;

	y = 0;
	opp = lvl->cam->sprite->opp;
	while (y < lvl->cam->size->y)
	{
		if (origin.y + y > lvl->canvas->size.y - 1 || (y + origin.y) < 0)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data
				+ (y * lvl->cam->size->x * opp),
				lvl->background->img_ptr->data
				+ (y * lvl->background->size.x * opp), lvl->cam->size->x * opp);
		}
		else if (deltax < lvl->cam->size->x * opp && xsize >= 0)
		{
			ft_memcpy(lvl->cam->sprite->img_ptr->data + deltax
				+ (y * lvl->cam->size->x * opp),
				lvl->canvas->sprite->img_ptr->data + ((y + origin.y)
					* lvl->canvas->size.x * opp) + origin.x * opp + deltax,
				xsize * opp - deltax);
		}
		y++;
	}
}

void	render_camera(t_level *lvl, t_vector2 origin)
{
	int	xsize;
	int	deltax;
	int	opp;
	int	camera_size;

	opp = lvl->cam->sprite->opp;
	camera_size = lvl->cam->size->x * opp;
	deltax = 0;
	xsize = lvl->cam->size->x;
	if (origin.x + lvl->cam->size->x > lvl->canvas->size.x)
		xsize -= origin.x + lvl->cam->size->x - lvl->canvas->size.x;
	if (origin.x < 0)
		deltax = -origin.x * opp;
	_render_canvas(lvl, origin, deltax, xsize);
	_render_top_part(lvl, origin, camera_size);
	_render_bot_part(lvl, origin, camera_size, xsize);
}

void	move_camera(t_game *game)
{
	double	new_posx;
	double	new_posy;

	if (!game->lvl->cam->dir.x && !game->lvl->cam->dir.y)
		return ;
	new_posx = game->lvl->cam->exact_pos.x
		+ (double)(game->lvl->cam->dir.x) * CAM_SPEED * game->elapsed;
	game->lvl->cam->exact_pos.x = new_posx;
	game->lvl->cam->pos->x = floor(new_posx);
	new_posy = game->lvl->cam->exact_pos.y
		+ (double)(game->lvl->cam->dir.y) * CAM_SPEED * game->elapsed;
	game->lvl->cam->exact_pos.y = new_posy;
	game->lvl->cam->pos->y = floor(new_posy);
}
