/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:04:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/24 17:51:36 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// returns 0 on no collision
// returns 1 on x collision
// returns 2 on y collision
// returns 3 on x y collision
static int	has_collision_at(t_game *game, int posx, int posy)
{
	int	letter_after_x;
	int	letter_after_y;
	int	new_posx;
	int	new_posy;

	new_posx = (posx)- ((double)(game->lvl->player->dir.x)
		* SPEED * game->elapsed * COLLISION_ERROR_DELTA);
	new_posy = (posy) - ((double)(game->lvl->player->dir.y) 
		* SPEED * game->elapsed * COLLISION_ERROR_DELTA);
	letter_after_x = letter_at_chunk(game->lvl, pos_to_chunk(game->lvl, new_posx, posy));
	letter_after_y = letter_at_chunk(game->lvl, pos_to_chunk(game->lvl, posx, new_posy));
	if (letter_after_x == '1' && letter_after_y != '1')
		return (1);
	if (letter_after_y == '1' && letter_after_x != '1')
		return (2);
	if (letter_after_y == '1' && letter_after_x == '1')
		return (3);
	return (0);
}

int	check_collision(t_game *game)
{
	int	ret;
	int	max;
	int	pos_at_sizex;
	int	pos_at_sizey;

	pos_at_sizex = game->lvl->player->pos->x + game->lvl->images[e_lplayer]->size.x;
	pos_at_sizey = game->lvl->player->pos->y + game->lvl->images[e_lplayer]->size.y;
	max = has_collision_at(game, game->lvl->player->pos->x, game->lvl->player->pos->y);
	ret = has_collision_at(game, pos_at_sizex, game->lvl->player->pos->y);
	if (ret > max)
		max = ret;
	ret = has_collision_at(game, game->lvl->player->pos->x, pos_at_sizey);
	if (ret > max)
		max = ret;
	ret = has_collision_at(game, pos_at_sizex, pos_at_sizey);
	if (ret > max)
		max = ret;
	return (max);
}
