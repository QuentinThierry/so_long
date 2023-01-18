/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/18 14:15:31 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game)
{
	find_chunk_under(game->canvas, game->layers[e_lplayer]);
	game->player->exact_pos.x += (double)(game->player->dir.x) * SPEED * game->elapsed;
	game->player->exact_pos.y += (double)(game->player->dir.y) * SPEED * game->elapsed;
	game->player->pos->x = floor(game->player->exact_pos.x);
	game->player->pos->y = floor(game->player->exact_pos.y);
	find_chunk_under(game->canvas, game->layers[e_lplayer]);
}

void	press_on_w(t_game *game, int is_release)
{
	if (!is_release)
		game->player->dir.y += -1;
	else
		game->player->dir.y += 1;
}

void	press_on_a(t_game *game, int is_release)
{
	if (!is_release)
		game->player->dir.x += -1;
	else
		game->player->dir.x += 1;
}

void	press_on_s(t_game *game, int is_release)
{
	if (!is_release)
		game->player->dir.y += 1;
	else
		game->player->dir.y += -1;
}

void	press_on_d(t_game *game, int is_release)
{
	if (!is_release)
		game->player->dir.x += 1;
	else
		game->player->dir.x += -1;
}

void	press_on_e(t_game *game, int is_release)
{
	clear_image(game->layers[e_ldebug]);
	(void)game;
	(void)is_release;
	//printf("Avant : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
	//printf("Apres : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
}