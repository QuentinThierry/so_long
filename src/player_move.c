/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/01 19:19:16 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	update_player_pos(t_game *game)
{
	game->lvl->player->sprite->pos = (t_vector2)
	{
		(SCREEN_WIDTH / 2 - game->lvl->player->sprite->size.x / 2) - game->lvl->canvas->origin.x,
		(SCREEN_HEIGHT / 2 -  game->lvl->player->sprite->size.y / 2) - game->lvl->canvas->origin.y
	};
}

void	move_canvas(t_game *game, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->canvas->exact_origin.x +
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->canvas->exact_origin.x = new_posx;
		game->lvl->canvas->origin.x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->canvas->exact_origin.y +
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->canvas->exact_origin.y = new_posy;
		game->lvl->canvas->origin.y = floor(new_posy);
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
		new_posx = game->lvl->canvas->exact_origin.x -
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->canvas->exact_origin.x = new_posx;
		game->lvl->canvas->origin.x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->canvas->exact_origin.y -
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->canvas->exact_origin.y = new_posy;
		game->lvl->canvas->origin.y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->player->sprite);
}

void	player_movement(t_game *game)
{
	t_collider	*colliding;

	move_canvas(game, 1, 0);
	update_player_pos(game);
	if (check_wall_collision(game->lvl))
	{
		reverse_move_player(game, 1, 0);
		update_player_pos(game);
	}
	move_canvas(game, 0, 1);
	update_player_pos(game);
	if (check_wall_collision(game->lvl))
	{
		reverse_move_player(game, 0, 1);
		update_player_pos(game);
	}
}
