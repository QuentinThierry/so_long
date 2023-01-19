/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/19 14:37:25 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game)
{
	find_chunk_under(game->lvl->canvas, game->lvl->images[e_lplayer]);
	game->lvl->player->exact_pos.x += (double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
	game->lvl->player->exact_pos.y += (double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
	game->lvl->player->pos->x = floor(game->lvl->player->exact_pos.x);
	game->lvl->player->pos->y = floor(game->lvl->player->exact_pos.y);
	find_chunk_under(game->lvl->canvas, game->lvl->images[e_lplayer]);
}

void	press_on_w(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += -1;
	else
		game->lvl->player->dir.y += 1;
}

void	press_on_a(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += -1;
	else
		game->lvl->player->dir.x += 1;
}

void	press_on_s(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += 1;
	else
		game->lvl->player->dir.y += -1;
}

void	press_on_d(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += 1;
	else
		game->lvl->player->dir.x += -1;
}

void	press_on_e(t_game *game, int is_release)
{
	clear_image(game->lvl->images[e_ldebug]);
	(void)game;
	(void)is_release;
	//printf("Avant : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
	//printf("Apres : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
}