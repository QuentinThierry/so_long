/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movement_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:58:39 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:26:57 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static inline void	set_enemy_pos_x(t_enemy *enemy, int delta)
{
	enemy->exact_pos.x = delta;
	enemy->pos->x = floor(enemy->exact_pos.x);
}

static inline void	set_enemy_pos_y(t_enemy *enemy, int delta)
{
	enemy->exact_pos.y = delta;
	enemy->pos->y = floor(enemy->exact_pos.y);
}

void	move_enemy(t_game *game, t_enemy *enemy,
		int is_x, int is_y)
{
	double	deltax;
	double	deltay;

	if (!enemy->dir.x && !enemy->dir.y)
		return ;
	if (is_x)
	{
		deltax = (double)(enemy->dir.x) * ENEMY_SPEED * game->elapsed;
		if (deltax > SIZE_CHUNK || deltax < -SIZE_CHUNK)
			deltax = (SIZE_CHUNK - 1) * enemy->dir.x;
		enemy->exact_pos.x += deltax;
		enemy->pos->x = floor(enemy->exact_pos.x);
	}
	if (is_y)
	{
		deltay = (double)(enemy->dir.y) * ENEMY_SPEED * game->elapsed;
		if (deltay > SIZE_CHUNK || deltay < -SIZE_CHUNK)
			deltay = (SIZE_CHUNK - 1) * enemy->dir.y;
		enemy->exact_pos.y += deltay;
		enemy->pos->y = floor(enemy->exact_pos.y);
	}
}

void	reverse_move_enemy(t_enemy *enemy,
		t_collider *collider, t_vector2 is_xy)
{
	if (!enemy->dir.x && !enemy->dir.y)
		return ;
	if (is_xy.x)
	{
		if (enemy->dir.x < 0)
			set_enemy_pos_x(enemy, collider->pos->x + SIZE_CHUNK);
		else
			set_enemy_pos_x(enemy, collider->pos->x - enemy->size->x);
	}
	if (is_xy.y)
	{
		if (enemy->dir.y < 0)
			set_enemy_pos_y(enemy, collider->pos->y + SIZE_CHUNK);
		else
			set_enemy_pos_y(enemy, collider->pos->y - enemy->size->y);
	}
}
