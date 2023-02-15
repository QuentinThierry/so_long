/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_enemies.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:30:28 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/15 18:42:24 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	_enemy_run_animation(t_enemy *enemy, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_RUN_E)
	{
		enemy->sprite->image_id++;
		if (enemy->sprite->image_id >= ANIM_NB_RUN_E
			+ e_enemy_run_0_0)
			enemy->sprite->image_id = e_enemy_run_0_0;
		gettimeofday(last_time, NULL);
	}
}

int	_enemy_idle_animation_base(t_enemy *enemy, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE0_E)
	{
		gettimeofday(last_time, NULL);
		enemy->sprite->image_id++;
		if (enemy->sprite->image_id >= ANIM_NB_IDLE0_E + e_enemy_idle_0_0)
		{
			enemy->sprite->image_id = e_enemy_idle_0_0;
			return (1);
		}
	}
	return (0);
}

void	_enemy_idle_animation_rare(t_enemy *enemy, struct timeval *last_time)
{
	struct timeval	time;
	double			delay;

	gettimeofday(&time, NULL);
	delay = (((double)(time.tv_usec - last_time->tv_usec) / CLOCKS_PER_SEC)
			+ time.tv_sec - last_time->tv_sec);
	if (delay >= ANIM_TIME_IDLE1_E)
	{
		enemy->sprite->image_id++;
		if (enemy->sprite->image_id >= ANIM_NB_IDLE1_E + e_enemy_idle_1_0)
			enemy->sprite->image_id = e_enemy_idle_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	play_anim_enemy(t_game *game, t_enemy *enemy)
{
	if (enemy->anim_time.tv_sec == 0 && enemy->anim_time.tv_usec == 0)
		enemy->anim_time = game->lvl->start_time;
	if (enemy->is_triggered)
	{
		if (enemy->sprite->image_id < e_enemy_run_0_0)
			enemy->sprite->image_id = e_enemy_run_0_0;
		_enemy_run_animation(enemy, &enemy->anim_time);
	}
	else
	{
		if (enemy->sprite->image_id >= e_enemy_run_0_0)
			enemy->sprite->image_id = e_enemy_idle_0_0;
		if (enemy->sprite->image_id >= e_enemy_idle_1_0)
			_enemy_idle_animation_rare(enemy, &enemy->anim_time);
		else
		{
			if (_enemy_idle_animation_base(enemy, &enemy->anim_time)
				&& (rand() % 100) < ANIM_RARE_IDLE_CHANCE_E)
				enemy->sprite->image_id = e_enemy_idle_1_0;
		}
	}
}
