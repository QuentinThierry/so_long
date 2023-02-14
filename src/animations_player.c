/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 05:04:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/14 05:07:14 by qthierry         ###   ########.fr       */
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
	if (delay >= ANIM_TIME_IDLE0)
	{
		gettimeofday(last_time, NULL);
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_IDLE + e_player_idle_0_0)
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
	if (delay >= ANIM_TIME_IDLE1)
	{
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_IDLE + e_player_idle_1_0)
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
	if (delay >= ANIM_TIME_RUN)
	{
		player->sprite->image_id++;
		if (player->sprite->image_id >= ANIM_NB_RUN
			+ e_player_run_0_0)
			player->sprite->image_id = e_player_run_0_0;
		gettimeofday(last_time, NULL);
	}
}

void	play_anim_player2(t_game *game)
{
	static struct timeval	anim_time = {0, 0};

	if (anim_time.tv_sec == 0 && anim_time.tv_usec == 0)
		anim_time = game->lvl->start_time;
	if (game->lvl->player2->dir.x || game->lvl->player2->dir.y)
	{
		if (game->lvl->player2->sprite->image_id < e_player_run_0_0)
			game->lvl->player2->sprite->image_id = e_player_run_0_0;
		_player_run_animation(game->lvl->player2, &anim_time);
	}
	else
	{
		if (game->lvl->player2->sprite->image_id >= e_player_run_0_0)
			game->lvl->player2->sprite->image_id = e_player_idle_0_0;
		if (game->lvl->player2->sprite->image_id >= e_player_idle_1_0)
			_player_idle_animation_rare(game->lvl->player2, &anim_time);
		else
		{
			if (_player_idle_animation_base(game->lvl->player2, &anim_time)
				&& (rand() % 100) < ANIM_RARE_IDLE_CHANCE)
				game->lvl->player2->sprite->image_id = e_player_idle_1_0;
		}
	}
}

void	play_anim_player1(t_game *game)
{
	static struct timeval	anim_time = {0, 0};

	if (anim_time.tv_sec == 0 && anim_time.tv_usec == 0)
		anim_time = game->lvl->start_time;
	if (game->lvl->player1->dir.x || game->lvl->player1->dir.y)
	{
		if (game->lvl->player1->sprite->image_id < e_player_run_0_0)
			game->lvl->player1->sprite->image_id = e_player_run_0_0;
		_player_run_animation(game->lvl->player1, &anim_time);
	}
	else
	{
		if (game->lvl->player1->sprite->image_id >= e_player_run_0_0)
			game->lvl->player1->sprite->image_id = e_player_idle_0_0;
		if (game->lvl->player1->sprite->image_id >= e_player_idle_1_0)
			_player_idle_animation_rare(game->lvl->player1, &anim_time);
		else
		{
			if (_player_idle_animation_base(game->lvl->player1, &anim_time)
				&& rand() % 100 < ANIM_RARE_IDLE_CHANCE)
				game->lvl->player1->sprite->image_id = e_player_idle_1_0;
		}
	}
}
