/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/05 03:18:11 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->player->exact_pos.x +
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->player->exact_pos.x = new_posx;
		game->lvl->player->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->player->exact_pos.y +
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->player->exact_pos.y = new_posy;
		game->lvl->player->pos->y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
}

void	reverse_move_player(t_game *game, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->player->exact_pos.x -
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->player->exact_pos.x = new_posx;
		game->lvl->player->pos->x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->player->exact_pos.y -
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->player->exact_pos.y = new_posy;
		game->lvl->player->pos->y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
}

void	player_movement(t_game *game)
{
	move_player(game, 1, 0);
	if (check_wall_collision(game->lvl))
		reverse_move_player(game, 1, 0);
	move_player(game, 0, 1);
	if (check_wall_collision(game->lvl))
		reverse_move_player(game, 0, 1);
}
