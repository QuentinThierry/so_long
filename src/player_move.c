/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/25 17:31:35 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->images[e_player]);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->canvas->draw_exact_pos.x +
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->canvas->draw_exact_pos.x = new_posx;
		game->lvl->canvas->draw_pos.x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->canvas->draw_exact_pos.y +
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->canvas->draw_exact_pos.y = new_posy;
		game->lvl->canvas->draw_pos.y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->images[e_player]);
}

void	reverse_move_player(t_game *game, int is_x, int is_y)
{
	double	new_posx;
	double	new_posy;

	find_chunk_under(game->lvl->canvas, game->lvl->images[e_player]);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	if (is_x)
	{
		new_posx = game->lvl->canvas->draw_exact_pos.x -
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->canvas->draw_exact_pos.x = new_posx;
		game->lvl->canvas->draw_pos.x = floor(new_posx);
	}
	if (is_y)
	{
		new_posy = game->lvl->canvas->draw_exact_pos.y -
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
		game->lvl->canvas->draw_exact_pos.y = new_posy;
		game->lvl->canvas->draw_pos.y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->images[e_player]);
}

void	press_on_w(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += 1;
	else
		game->lvl->player->dir.y += -1;
	
}

void	press_on_a(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += 1;
	else
		game->lvl->player->dir.x += -1;
}

void	press_on_s(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += -1;
	else
		game->lvl->player->dir.y += 1;
}

void	press_on_d(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += -1;
	else
		game->lvl->player->dir.x += 1;
}

void	press_on_e(t_game *game, int is_release)
{
	(void)game;
	(void)is_release;
}