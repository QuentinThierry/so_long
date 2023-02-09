/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:55 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/09 19:41:45 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_calculate_enemy_dir(t_game *game, int id)
{
	game->lvl->enemies[id]->dir = 
		direction_normalized(*game->lvl->enemies[id]->pos,
		*game->lvl->player->pos);
}

static void	_move_enemy(t_game *game, int id, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
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
	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
}

static void	_reverse_move_enemy(t_game *game, int id, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
	if (!game->lvl->enemies[id]->dir.x && !game->lvl->enemies[id]->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->enemies[id]->exact_pos.x -
				game->lvl->enemies[id]->dir.x * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.x = new_posx;
		game->lvl->enemies[id]->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->enemies[id]->exact_pos.y -
				game->lvl->enemies[id]->dir.y * ENEMY_SPEED * game->elapsed;
		game->lvl->enemies[id]->exact_pos.y = new_posy;
		game->lvl->enemies[id]->pos->y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->enemies[id]->sprite);
}

void	check_trigger_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (!game->lvl->enemies[i]->is_triggered
			&& is_inside_load_range(game, *game->lvl->enemies[i]->pos))
		{
			if (distance(*game->lvl->enemies[i]->pos, *game->lvl->player->pos)
				< DISTANCE_AGGRO)
			{
				game->lvl->enemies[i]->is_triggered = 1;
				game->lvl->enemies[i]->sprite->image_id = e_enemy_1_0;
			}
			else
				game->lvl->enemies[i]->sprite->image_id = e_enemy_0_0;
		}
		else
			game->lvl->enemies[i]->is_triggered = 0;
		++i;
	}
}

void	enemy_movement(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (game->lvl->enemies[i]->is_triggered)
		{
			_calculate_enemy_dir(game, i);
			_move_enemy(game, i, 1, 0);
			if (check_wall_collision(game->lvl, game->lvl->enemies[i]->collider))
				_reverse_move_enemy(game, i, 1, 0);
			_move_enemy(game, i, 0, 1);
			if (check_wall_collision(game->lvl, game->lvl->enemies[i]->collider))
				_reverse_move_enemy(game, i, 0, 1);
		}
		i++;
	}
}
