/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/16 20:15:37 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	exec_on_w(t_game *game)
{
	game->player->pos->y -= SPEED;
	//printf("W\n");
}

void	exec_on_a(t_game *game)
{
	game->player->pos->x -= SPEED;
	//printf("A\n");
}

void	exec_on_s(t_game *game)
{
	game->player->pos->y += SPEED;
	//printf("S\n");
}

void	exec_on_d(t_game *game)
{
	game->player->pos->x += SPEED;
	//printf("D\n");
}

void	exec_on_e(t_game *game)
{
	flip_image_y(game->layers[e_lplayer]);
	//printf("Avant : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
	// rotate_player(game->player, 1);
	//printf("Apres : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
}