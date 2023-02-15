/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:42:19 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/15 18:42:30 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	camera_animation_to_exit(t_level *lvl)
{
	struct timeval	time;
	double			delay;
	float			dist;
	t_vector2		exit_pos;
	t_fvector2		dir;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - lvl->start_time.tv_usec)
				/ CLOCKS_PER_SEC) + time.tv_sec - lvl->start_time.tv_sec);
	if (delay >= CAM_ANIM_TIME_SEC)
		lvl->is_animating_cam = 0;
	return ;
	if (delay >= CAM_ANIM_TIME_SEC)
		delay = CAM_ANIM_TIME_SEC;
	exit_pos = lvl->canvas->chunks[find_exit_chunk(lvl->map)].pos;
	dist = distance(*lvl->player1->pos, exit_pos);
	dir = direction_normalized(*lvl->player1->pos, exit_pos);
	*lvl->cam->pos = (t_vector2){(lvl->player1->pos->x) + (dir.x * dist)
		* (delay / CAM_ANIM_TIME_SEC) - (((float)SCREEN_WIDTH / 2)
			+ (float)lvl->player1->sprite->size.x / 2),
		(lvl->player1->pos->y) + dir.y * dist * (delay / CAM_ANIM_TIME_SEC)
		- (((float)SCREEN_HEIGHT / 2)
			+ (float)lvl->player1->sprite->size.y / 2),
	};
}

void	play_animations(t_game *game)
{
	int	i;

	play_anim_player1(game);
	if (game->lvl->player2)
		play_anim_player2(game);
	i = 0;
	while (game->lvl->enemies[i])
	{
		if (is_inside_load_range(game, *game->lvl->enemies[i]->pos))
			play_anim_enemy(game, game->lvl->enemies[i]);
		i++;
	}
}
