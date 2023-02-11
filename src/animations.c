/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:42:19 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/11 18:08:53 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <sys/time.h>

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
	if (delay >= CAM_ANIM_TIME_SEC + 1)
		game->lvl->is_animating_cam = 0;
	else
	{
		if (delay >= CAM_ANIM_TIME_SEC)
			delay = CAM_ANIM_TIME_SEC;
		exit_pos = game->lvl->canvas->chunks[find_exit_chunk(game->lvl->map)].pos;
		dist = distance(*game->lvl->player->pos, exit_pos);
		dir = direction_normalized(*game->lvl->player->pos, exit_pos);
		*game->lvl->cam->pos = (t_vector2){
			(game->lvl->player->pos->x) + (dir.x * dist) * (delay / CAM_ANIM_TIME_SEC)
			- (((float)SCREEN_WIDTH / 2) + (float)game->lvl->player->sprite->size.x / 2),
			(game->lvl->player->pos->y) + dir.y * dist * (delay / CAM_ANIM_TIME_SEC)
			- (((float)SCREEN_HEIGHT / 2) + (float)game->lvl->player->sprite->size.y / 2),
		};
	}
}

int	_player_idle_animation_base(t_game *game, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
		+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE0)
	{
		gettimeofday(last_time, NULL);
		game->lvl->player->sprite->image_id++;
		if (game->lvl->player->sprite->image_id >= ANIM_NB_IDLE
			+ e_player_idle_0_0)
		{
			game->lvl->player->sprite->image_id = e_player_idle_0_0;
			return (1);
		}
	}
	return (0);
}

void	_player_idle_animation_rare(t_game *game, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
		+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE1)
	{
		game->lvl->player->sprite->image_id++;
		if (game->lvl->player->sprite->image_id >= ANIM_NB_IDLE
			+ e_player_idle_1_0)
			game->lvl->player->sprite->image_id = e_player_idle_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	_player_run_animation(t_game *game, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
		+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_RUN)
	{
		game->lvl->player->sprite->image_id++;
		if (game->lvl->player->sprite->image_id >= ANIM_NB_RUN
			+ e_player_run_0_0)
			game->lvl->player->sprite->image_id = e_player_run_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	play_animations(t_game *game)
{
	static struct timeval	anim_time = {0, 0};

	if (anim_time.tv_sec == 0 && anim_time.tv_usec == 0)
		anim_time = game->lvl->start_time;
	if (game->lvl->player->dir.x || game->lvl->player->dir.y)
	{
		if (game->lvl->player->sprite->image_id < e_player_run_0_0)
			game->lvl->player->sprite->image_id = e_player_run_0_0;
		_player_run_animation(game, &anim_time);
	}
	else
	{
		if (game->lvl->player->sprite->image_id >= e_player_run_0_0)
			game->lvl->player->sprite->image_id = e_player_idle_0_0;
		if (game->lvl->player->sprite->image_id >= e_player_idle_1_0)
			_player_idle_animation_rare(game, &anim_time);
		else
		{
			if(_player_idle_animation_base(game, &anim_time)
				&& rand() % 100 < ANIM_RARE_IDLE_CHANCE)
				game->lvl->player->sprite->image_id = e_player_idle_1_0;
		}
	}
}