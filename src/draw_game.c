/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:18:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/11 02:32:12 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"

static void	_draw_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (is_inside_load_range(game, *game->lvl->enemies[i]->pos))
		{
			game->lvl->enemies[i]->sprite->img_ptr
				= game->lvl->images[game->lvl->enemies[i]->sprite->image_id];
			draw_image_on_image(game->lvl->canvas->sprite,
				game->lvl->enemies[i]->sprite, *game->lvl->enemies[i]->pos, 1);
		}
		++i;
	}
}

static void	_draw_player(t_game *game)
{
	game->lvl->player->sprite->img_ptr
		= game->lvl->images[game->lvl->player->sprite->image_id];
	draw_image_on_image(game->lvl->canvas->sprite, game->lvl->player->sprite,
			game->lvl->player->sprite->pos, 1);
}

int	draw_on_window(t_game *game)
{
	_draw_enemies(game);
	_draw_player(game);
	render_camera(game->lvl, *game->lvl->cam->pos);
	if (ISDEBUG)
		debug_calculate(game->lvl);
	mlx_put_image_to_window(game->mlx, game->window,
			game->lvl->cam->sprite->img_ptr, 0, 0);
	return (0);
}