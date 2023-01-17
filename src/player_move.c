/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/17 00:57:00 by qthierry         ###   ########.fr       */
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
	rotate_image(game->layers[e_lplayer], 1);

	//flip_image_x(game->layers[e_lplayer]);
	//printf("Avant : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
	//printf("Apres : (%d, %d)\n", mlx->player->pos.x, mlx->player->pos.y);
}