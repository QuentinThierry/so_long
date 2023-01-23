/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:04:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/23 19:54:46 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// returns 0 on no collision
// returns 1 on x collision
// returns 2 on y collision
// returns 3 on x y collision
int	check_collision(t_game *game)
{
	int	letter_after_x;
	int	letter_after_y;
	int	new_posx;
	int	new_posy;

	new_posx = ((double)game->lvl->player->pos->x)
		- (double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
	new_posy = ((double)game->lvl->player->pos->y)
		- (double)(game->lvl->player->dir.y) * SPEED * game->elapsed;
	letter_after_x = letter_at_chunk(game->lvl, pos_to_chunk(game->lvl, new_posx, game->lvl->player->pos->y));
	letter_after_y = letter_at_chunk(game->lvl, pos_to_chunk(game->lvl, game->lvl->player->pos->x, new_posy));
	if (letter_after_x == '1' && letter_after_y != '1')
		return (1);
	if (letter_after_y == '1' && letter_after_x != '1')
		return (2);
	if (letter_after_y == '1' && letter_after_x == '1')
		return (3);
	return (0);
}
