/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:18:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/20 17:48:04 by qthierry         ###   ########.fr       */
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
			if (game->lvl->enemies[i]->is_look_left < 0)
				flip_image_y(game->lvl->enemies[i]->sprite);
			blend_image_to_image(game->lvl->canvas->sprite,
				game->lvl->enemies[i]->sprite,
				*game->lvl->enemies[i]->pos);
			if (game->lvl->enemies[i]->is_look_left < 0)
				flip_image_y(game->lvl->enemies[i]->sprite);
		}
		++i;
	}
}

static void	_draw_player1(t_game *game)
{
	if (!is_inside_load_range(game, *game->lvl->player1->pos))
		return ;
	game->lvl->player1->sprite->img_ptr
		= game->lvl->images[game->lvl->player1->sprite->image_id];
	if (game->lvl->player1->is_look_left == 1)
		flip_image_y(game->lvl->player1->sprite);
	blend_image_to_image(game->lvl->canvas->sprite, game->lvl->player1->sprite,
		*game->lvl->player1->pos);
	if (game->lvl->player1->is_look_left == 1)
		flip_image_y(game->lvl->player1->sprite);
}

static void	_draw_player2(t_game *game)
{
	if (!is_inside_load_range(game, *game->lvl->player2->pos))
		return ;
	game->lvl->player2->sprite->img_ptr
		= game->lvl->images[game->lvl->player2->sprite->image_id];
	if (game->lvl->player2->is_look_left == 1)
		flip_image_y(game->lvl->player2->sprite);
	blend_image_to_image(game->lvl->canvas->sprite, game->lvl->player2->sprite,
		*game->lvl->player2->pos);
	if (game->lvl->player2->is_look_left == 1)
		flip_image_y(game->lvl->player2->sprite);
}

void	draw_ui(t_game *game)
{
	blend_image_to_image(game->lvl->cam->sprite, game->lvl->ui, game->lvl->ui->pos);
	// mlx_string_put(game->mlx, game->window, 500, 500, RED, ft_itoa(game->lvl->nb_move));
}

int	draw_on_window(t_game *game)
{
	_draw_enemies(game);
	_draw_player1(game);
	if (game->lvl->player2)
		_draw_player2(game);
	render_camera(game->lvl, *game->lvl->cam->pos);
	draw_arrow_to_end(game->lvl, game->lvl->player1);
	draw_ui(game);
	if (game->is_end)
		end_game(game);
	else if (ISDEBUG)
	{
		debug_calculate(game->lvl);
		a_star(game, *game->lvl->player1->pos, NULL);
		if (game->lvl->player2)
			a_star(game, *game->lvl->player2->pos, NULL);
	}
	return (0);
}
