/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:30:53 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/23 20:07:12 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game)
{
	double	new_posx;
	double	new_posy;
	int		collision_type;

	find_chunk_under(game->lvl->canvas, game->lvl->images[e_lplayer]);
	if (!game->lvl->player->dir.x && !game->lvl->player->dir.y)
		return ;
	collision_type = check_collision(game);
	if (collision_type == 3)
		return ;
	if (collision_type == 2 || !collision_type)
	{
		new_posx = game->lvl->canvas->draw_exact_pos.x +
				(double)(game->lvl->player->dir.x) * SPEED * game->elapsed;
		game->lvl->canvas->draw_exact_pos.x = new_posx;
		game->lvl->canvas->draw_pos.x = floor(new_posx);
	}
	if (collision_type == 1 || !collision_type)
	{
		new_posy = game->lvl->canvas->draw_exact_pos.y +
				(double)(game->lvl->player->dir.y) * SPEED * game->elapsed;;
		game->lvl->canvas->draw_exact_pos.y = new_posy;
		game->lvl->canvas->draw_pos.y = floor(new_posy);
	}
	find_chunk_under(game->lvl->canvas, game->lvl->images[e_lplayer]);
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
	clear_image(game->lvl->images[e_ldebug]);
	(void)game;
	(void)is_release;
}