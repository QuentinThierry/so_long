/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:18:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 15:41:16 by qthierry         ###   ########.fr       */
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
	int		moves_posx;
	int		moves_posy;
	int		collec_posx;
	int		collec_posy;
	char	*str;

	moves_posx = game->lvl->ui->pos.x + (game->lvl->ui->size.x / 4);
	moves_posy = game->lvl->ui->pos.y + (game->lvl->ui->size.y / 2);
	blend_image_to_image(game->lvl->cam->sprite,
		game->lvl->ui, game->lvl->ui->pos);
	collec_posx = game->lvl->ui->pos.x + ((game->lvl->ui->size.x / 4) * 3);
	collec_posy = game->lvl->ui->pos.y + (game->lvl->ui->size.y / 2);
	str = ft_itoa(game->lvl->nb_move);
	if (!str)
		exit_game(game, "Error\nAllocation error.\n");
	mlx_string_put(game->mlx, game->window, moves_posx, moves_posy,
		DARK_GRAY, str);
	free(str);
	str = ft_itoa(game->lvl->nb_collec);
	if (!str)
		exit_game(game, "Error\nAllocation error.\n");
	mlx_string_put(game->mlx, game->window, collec_posx, collec_posy,
		DARK_GRAY, str);
	free(str);
}

int	draw_on_window(t_game *game)
{
	_draw_enemies(game);
	_draw_player1(game);
	if (game->lvl->player2)
		_draw_player2(game);
	render_camera(game->lvl, *game->lvl->cam->pos);
	if (!is_inside_load_range(game,
			game->lvl->canvas->chunks[game->lvl->exit_chunk].pos))
		draw_arrow_to_end(game->lvl, game->lvl->player1);
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
