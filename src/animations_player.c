/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 05:04:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 21:54:35 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	_player_idle_animation_base(t_player *player, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE0_P)
	{
		gettimeofday(last_time, NULL);
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_IDLE_P + e_player_idle_0_0)
		{
			player->sprite->image_id = e_player_idle_0_0;
			return (1);
		}
	}
	return (0);
}

void	_player_idle_animation_rare(t_player *player, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE1_P)
	{
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_IDLE_P + e_player_idle_1_0)
			player->sprite->image_id = e_player_idle_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	_player_run_animation(t_player *player, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_RUN_P)
	{
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_RUN_P
			+ e_player_run_0_0)
			player->sprite->image_id = e_player_run_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	play_anim_player2(t_level *lvl, int is_end)
{
	static struct timeval	anim_time = {0, 0};

	if (anim_time.tv_sec == 0 && anim_time.tv_usec == 0)
		anim_time = lvl->start_time;
	if ((lvl->player2->dir.x || lvl->player2->dir.y) && !is_end)
	{
		if (lvl->player2->sprite->image_id < e_player_run_0_0)
			lvl->player2->sprite->image_id = e_player_run_0_0;
		_player_run_animation(lvl->player2, &anim_time);
	}
	else
	{
		if (lvl->player2->sprite->image_id >= e_player_run_0_0)
			lvl->player2->sprite->image_id = e_player_idle_0_0;
		if (lvl->player2->sprite->image_id >= e_player_idle_1_0)
			_player_idle_animation_rare(lvl->player2, &anim_time);
		else
		{
			if (_player_idle_animation_base(lvl->player2, &anim_time)
				&& (rand() % 100) < ANIM_RARE_IDLE_CHANCE_P)
				lvl->player2->sprite->image_id = e_player_idle_1_0;
		}
	}
	if (lvl->is_animating_cam)
		find_chunk_under(lvl->canvas, lvl->player2->sprite);
}

void	play_anim_player1(t_level *lvl, int is_end)
{
	static struct timeval	anim_time = {0, 0};

	if (anim_time.tv_sec == 0 && anim_time.tv_usec == 0)
		anim_time = lvl->start_time;
	if ((lvl->player1->dir.x || lvl->player1->dir.y) && !is_end)
	{
		if (lvl->player1->sprite->image_id < e_player_run_0_0)
			lvl->player1->sprite->image_id = e_player_run_0_0;
		_player_run_animation(lvl->player1, &anim_time);
	}
	else
	{
		if (lvl->player1->sprite->image_id >= e_player_run_0_0)
			lvl->player1->sprite->image_id = e_player_idle_0_0;
		if (lvl->player1->sprite->image_id >= e_player_idle_1_0)
			_player_idle_animation_rare(lvl->player1, &anim_time);
		else
		{
			if (_player_idle_animation_base(lvl->player1, &anim_time)
				&& rand() % 100 < ANIM_RARE_IDLE_CHANCE_P)
				lvl->player1->sprite->image_id = e_player_idle_1_0;
		}
	}
	if (lvl->is_animating_cam)
		find_chunk_under(lvl->canvas, lvl->player1->sprite);
}
