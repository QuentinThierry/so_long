/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/14 03:10:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_move_player(t_game *game, t_player *player,
		int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	if (!player->dir.x && !player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = player->exact_pos.x +
				(double)(player->dir.x) * SPEED * game->elapsed;
		player->exact_pos.x = new_posx;
		player->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = player->exact_pos.y +
				(double)(player->dir.y) * SPEED * game->elapsed;
		player->exact_pos.y = new_posy;
		player->pos->y = floor(new_posy);
	}
}

static inline void	set_player_pos_x(t_player *player, int delta)
{
	player->exact_pos.x = delta;
	player->pos->x = floor(player->exact_pos.x);
}

static inline void	set_player_pos_y(t_player *player, int delta)
{
	player->exact_pos.y = delta;
	player->pos->y = floor(player->exact_pos.y);
}

static void	_reverse_move_player(t_player *player,
		t_collider *collider, t_vector2 is_xy)
{
	if (!player->dir.x && !player->dir.y)
		return ;
	if (is_xy.x)
	{
		if (player->dir.x < 0)
			set_player_pos_x(player, collider->pos->x + SIZE_CHUNK);
		else
			set_player_pos_x(player, collider->pos->x - PLAYER_WIDTH);
	}
	if (is_xy.y)
	{
		if (player->dir.y < 0)
			set_player_pos_y(player, collider->pos->y + SIZE_CHUNK);
		else
			set_player_pos_y(player, collider->pos->y - PLAYER_HEIGHT);
	}
}

// static void	_reverse_move_player(t_player *player,
// 		t_collider *collider, t_vector2 is_xy)
// {
// 	if (!player->dir.x && !player->dir.y)
// 		return ;
// 	if (is_xy.x)
// 	{
// 		if (player->dir.x < 0)
// 		{
// 			player->exact_pos.x = collider->pos->x + SIZE_CHUNK;
// 			player->pos->x = floor(player->exact_pos.x);
// 		}
// 		else
// 		{
// 			player->exact_pos.x = collider->pos->x - PLAYER_WIDTH;
// 			player->pos->x = floor(player->exact_pos.x);
// 		}
// 	}
// 	if (is_xy.y)
// 	{
// 		if (player->dir.y < 0)
// 		{
// 			player->exact_pos.y = collider->pos->y + SIZE_CHUNK;
// 			player->pos->y = floor(player->exact_pos.y);
// 		}
// 		else
// 		{
// 			player->exact_pos.y = collider->pos->y - PLAYER_HEIGHT;
// 			player->pos->y = floor(player->exact_pos.y);
// 		}
// 	}
// }

void	player_movement(t_game *game, t_player *player)
{
	t_collider *collider;

	if (player->dir.x)
		player->is_look_left = -player->dir.x;
	if (player == game->lvl->player2)
		player->is_look_left = -player->dir.x;
	find_chunk_under(game->lvl->canvas, player->sprite);
	_move_player(game, player, 1, 0);
	collider = check_wall_collision(game->lvl, player->collider);
	if (collider)
		_reverse_move_player(player, collider, (t_vector2){1, 0});
	_move_player(game, player, 0, 1);
	collider = check_wall_collision(game->lvl, player->collider);
	if (collider)
		_reverse_move_player(player, collider, (t_vector2){0, 1});
	find_chunk_under(game->lvl->canvas, player->sprite);
}
