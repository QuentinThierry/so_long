/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:55 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 19:14:43 by qthierry         ###   ########.fr       */
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

static void	_move_enemy(t_game *game, int id, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	if (!game->lvl->enemies[id]->dir.x && !game->lvl->enemies[id]->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->enemies[id]->exact_pos.x +
				game->lvl->enemies[id]->dir.x * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.x = new_posx;
		game->lvl->enemies[id]->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->enemies[id]->exact_pos.y +
				game->lvl->enemies[id]->dir.y * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.y = new_posy;
		game->lvl->enemies[id]->pos->y = floor(new_posy);
	}
}

static void	_reverse_move_enemy(t_enemy *enemy,
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

void	check_trigger_enemy(t_game *game, t_player *player)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (is_inside_load_range(game, *game->lvl->enemies[i]->pos))
		{
			if (sqrdistance(*game->lvl->enemies[i]->pos, *player->pos)
				< DISTANCE_AGGRO)
			{
				game->lvl->enemies[i]->is_triggered = 1;
				game->lvl->enemies[i]->target = player;
			}
			else if (game->lvl->enemies[i]->target == player)
			{
				game->lvl->enemies[i]->is_triggered = 0;
				game->lvl->enemies[i]->target = NULL;
			}
		}
		++i;
	}
}

void	enemy_movement(t_game *game)
{
	int			i;
	t_collider	*collider;
	t_enemy		*enemy;

	i = -1;
	while (game->lvl->enemies[++i])
	{
		enemy = game->lvl->enemies[i];
		if (!is_inside_load_range(game, *enemy->pos))
			continue ;
		find_chunk_under(game->lvl->canvas, enemy->sprite);
		if (enemy->is_triggered)
		{
			enemy->dir = direction_normalized(*enemy->pos,
					*enemy->target->pos);
			_move_enemy(game, i, 1, 0);
			collider = check_wall_collision(game->lvl, enemy->collider);
			if (collider)
				_reverse_move_enemy(enemy, collider, (t_vector2){1, 0});
			_move_enemy(game, i, 0, 1);
			collider = check_wall_collision(game->lvl, enemy->collider);
			if (collider)
				_reverse_move_enemy(enemy, collider, (t_vector2){0, 1});

			find_chunk_under(game->lvl->canvas, enemy->sprite);
		}
	}
}
