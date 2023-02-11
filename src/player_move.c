/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/11 21:50:57 by qthierry         ###   ########.fr       */
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

static void	_reverse_move_player(t_game *game, t_player *player,
		int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	if (!player->dir.x && !player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = player->exact_pos.x -
				(double)(player->dir.x) * SPEED * game->elapsed;
		player->exact_pos.x = new_posx;
		player->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = player->exact_pos.y -
				(double)(player->dir.y) * SPEED * game->elapsed;
		player->exact_pos.y = new_posy;
		player->pos->y = floor(new_posy);
	}
}

void	player_movement(t_game *game, t_player *player)
{
	if (player->dir.x)
		player->is_look_left = -player->dir.x;
	if (player == game->lvl->player2)
		player->is_look_left = -player->dir.x;
	find_chunk_under(game->lvl->canvas, player->sprite);
	_move_player(game, player, 1, 0);
	if (check_wall_collision(game->lvl, player->collider))
		_reverse_move_player(game, player, 1, 0);
	_move_player(game, player, 0, 1);
	if (check_wall_collision(game->lvl, player->collider))
		_reverse_move_player(game, player, 0, 1);
	find_chunk_under(game->lvl->canvas, player->sprite);
}
