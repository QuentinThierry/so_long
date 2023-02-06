/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:18:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/06 20:19:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"

static void	_draw_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		draw_image_on_canvas(game->lvl->canvas, game->lvl->enemies[i]->sprite, *game->lvl->enemies[i]->pos, 0);
		++i;
	}
}

static void	_draw_player(t_game *game)
{
	draw_image_on_canvas(game->lvl->canvas, game->lvl->player->sprite,
		game->lvl->player->sprite->pos, 1);
}

int	draw_on_window(t_game *game)
{

	_draw_enemies(game);
	_draw_player(game);
	render_camera(game->lvl, game->lvl->cam->pos);
	mlx_put_image_to_window(game->mlx, game->window, game->lvl->cam->img_ptr, 0, 0);
	return (0);
}