/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:42:19 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/05 18:08:58 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	camera_animation_to_exit(t_game *game)
{
	struct timeval	time;
	double			delay;
	float			dist;
	t_vector2		exit_pos;
	t_fvector2		dir;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - game->lvl->start_time.tv_usec) / CLOCKS_PER_SEC)
		+ time.tv_sec - game->lvl->start_time.tv_sec);
	if (delay >= CAM_ANIM_TIME_SEC)
		game->lvl->is_animating_cam = 0;
	else
	{
		exit_pos = game->lvl->canvas->chunks[find_exit_chunk(game->lvl->map)].pos;
		dist = distance(*game->lvl->player->pos, exit_pos);
		dir = (t_fvector2){exit_pos.x - game->lvl->player->pos->x, exit_pos.y - game->lvl->player->pos->y};
		dir = normalize((t_vector2){dir.x, dir.y});
		game->lvl->cam->pos = (t_vector2){
			(game->lvl->player->pos->x) + (dir.x * dist) * (delay / CAM_ANIM_TIME_SEC)
			- (((float)SCREEN_WIDTH / 2) + (float)game->lvl->player->sprite->size.x / 2),
			(game->lvl->player->pos->y) + dir.y * dist * (delay / CAM_ANIM_TIME_SEC)
			- (((float)SCREEN_HEIGHT / 2) + (float)game->lvl->player->sprite->size.y / 2),
		};
	}
}
