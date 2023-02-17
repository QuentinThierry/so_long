/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:02:14 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 01:12:49 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_vector2	get_offset_for_cam(t_camera *cam, t_vector2 pos_to_offset)
{
	return ((t_vector2)
	{
		pos_to_offset.x - cam->pos->x,
		pos_to_offset.y - cam->pos->y
	});
}

int	is_inside_load_range(t_game *game, t_vector2 pos)
{
	return (pos.x > game->lvl->cam->pos->x - OFFSET_CAM_LOAD
		&& pos.x < game->lvl->cam->pos->x
			+ game->lvl->cam->size->x + OFFSET_CAM_LOAD
		&& pos.y < game->lvl->cam->pos->y
			+ game->lvl->cam->size->y + OFFSET_CAM_LOAD
		&& pos.y > game->lvl->cam->pos->y - OFFSET_CAM_LOAD);
}

int	is_inside_camera(t_camera *cam, t_vector2 pos)
{
	t_vector2	pos2;

	pos2 = get_offset_for_cam(cam, *cam->pos);
	return (pos.x > pos2.x && pos.x < pos2.x + cam->size->x
		&& pos.y < pos2.y + cam->size->y && pos.y > pos2.y);
}
