/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:18:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/13 21:00:39 by qthierry         ###   ########.fr       */
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
				game->lvl->enemies[i]->sprite, *game->lvl->enemies[i]->pos, HIGH_GRPHISM);
		}
		++i;
	}
}

static void	_draw_player1(t_game *game)
{
	game->lvl->player1->sprite->img_ptr
		= game->lvl->images[game->lvl->player1->sprite->image_id];
	if (game->lvl->player1->is_look_left == 1)
		flip_image_y(game->lvl->player1->sprite);
	draw_image_on_image(game->lvl->canvas->sprite, game->lvl->player1->sprite,
			game->lvl->player1->sprite->pos, 1);
	if (game->lvl->player1->is_look_left == 1)
		flip_image_y(game->lvl->player1->sprite);
}

static void	_draw_player2(t_game *game)
{
	game->lvl->player2->sprite->img_ptr
		= game->lvl->images[game->lvl->player2->sprite->image_id];
	if (game->lvl->player2->is_look_left == 1)
		flip_image_y(game->lvl->player2->sprite);
	draw_image_on_image(game->lvl->canvas->sprite, game->lvl->player2->sprite,
			game->lvl->player2->sprite->pos, 1);
	if (game->lvl->player2->is_look_left == 1)
		flip_image_y(game->lvl->player2->sprite);
}

static void	_draw_players(t_game *game)
{
	_draw_player1(game);
	if (game->lvl->player2)
		_draw_player2(game);
}

int	draw_on_window(t_game *game)
{
	_draw_enemies(game);
	_draw_players(game);
	render_camera(game->lvl, *game->lvl->cam->pos);
	if (ISDEBUG)
		debug_calculate(game->lvl);
	mlx_put_image_to_window(game->mlx, game->window,
			game->lvl->cam->sprite->img_ptr, 0, 0);
	return (0);
}