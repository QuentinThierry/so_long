/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:55 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:00:07 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

inline static void	_deplacement(t_game *game, t_enemy *enemy)
{
	t_collider	*collider;

	enemy->dir = direction_normalized(*enemy->pos,
			*enemy->target->pos);
	move_enemy(game, enemy, 1, 0);
	collider = check_wall_collision(game->lvl, enemy->collider);
	if (collider)
		reverse_move_enemy(enemy, collider, (t_vector2){1, 0});
	move_enemy(game, enemy, 0, 1);
	collider = check_wall_collision(game->lvl, enemy->collider);
	if (collider)
		reverse_move_enemy(enemy, collider, (t_vector2){0, 1});
	find_chunk_under(game->lvl->canvas, enemy->sprite);
}

void	enemy_movement(t_game *game)
{
	int			i;
	t_enemy		*enemy;

	i = -1;
	while (game->lvl->enemies[++i])
	{
		enemy = game->lvl->enemies[i];
		if (enemy->dir.x < 0)
			enemy->is_look_left = 1;
		else
			enemy->is_look_left = -1;
		if (!is_inside_load_range(game, *enemy->pos))
			continue ;
		find_chunk_under(game->lvl->canvas, enemy->sprite);
		if (enemy->is_triggered)
			_deplacement(game, enemy);
	}
}
