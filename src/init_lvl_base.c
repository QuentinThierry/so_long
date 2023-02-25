/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lvl_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:45:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:07:39 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_init_player1(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->player1->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->player1->collider = ft_calloc(sizeof(t_collider), 1);
	if (!(lvl->player1->sprite && lvl->player1->collider))
		exit_game(game, "Error\nAllocation error.\n");
	lvl->player1->collider->id = 0;
	lvl->player1->collider->pos = &lvl->player1->sprite->pos;
	lvl->player1->collider->size = &lvl->player1->sprite->size;
	lvl->player1->dir = (t_vector2){0, 0};
	lvl->player1->is_look_left = 0;
	lvl->player1->sprite->image_id = e_player_idle_0_0;
	btmlx_get_addr(lvl->player1->sprite,
		lvl->images[e_player_idle_0_0]);
	lvl->player1->pos = &lvl->player1->sprite->pos;
}

void	init_player2(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->player2 = ft_calloc(sizeof(t_player), 1);
	if (!lvl->player2)
		exit_game(game, "Error\nAllocation error.\n");
	lvl->player2->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->player2->collider = ft_calloc(sizeof(t_collider), 1);
	if (!(lvl->player2->sprite && lvl->player2->collider))
		exit_game(game, "Error\nAllocation error.\n");
	lvl->player2->collider->id = 0;
	lvl->player2->collider->pos = &lvl->player2->sprite->pos;
	lvl->player2->collider->size = &lvl->player2->sprite->size;
	lvl->player2->dir = (t_vector2){0, 0};
	lvl->player2->is_look_left = 0;
	lvl->player2->sprite->image_id = e_player_idle_0_0;
	btmlx_get_addr(lvl->player2->sprite,
		lvl->images[e_player_idle_0_0]);
	lvl->player2->pos = &lvl->player2->sprite->pos;
	*lvl->player2->pos = *lvl->player1->pos;
	lvl->player2->exact_pos
		= (t_fvector2){lvl->player1->pos->x, lvl->player1->pos->y};
}

static void	init_lvl_base2(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	if (ISDEBUG)
	{
		lvl->debug_sprite = ft_calloc(sizeof(t_sprite), 1);
		lvl->debug_tile_sprite = ft_calloc(sizeof(t_sprite), 1);
		if (!(lvl->debug_sprite && lvl->debug_tile_sprite))
			exit_game(game, "Error\nAllocation error.\n");
		lvl->debug_sprite->image_id = e_debug;
		lvl->debug_tile_sprite->image_id = e_debug_tile;
		btmlx_get_addr(lvl->debug_sprite, lvl->images[e_debug]);
		btmlx_get_addr(lvl->debug_tile_sprite, lvl->images[e_debug_tile]);
	}
	lvl->nb_collec = 0;
	lvl->max_collec = 0;
	lvl->nb_move = 0;
	init_canvas(game);
	init_camera(game);
	init_background(game);
	_init_player1(game);
}

void	init_lvl_base(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->canvas = ft_calloc(sizeof(t_canvas), 1);
	lvl->player1 = ft_calloc(sizeof(t_player), 1);
	lvl->arrow = ft_calloc(sizeof(t_sprite), 1);
	lvl->ui = ft_calloc(sizeof(t_sprite), 1);
	lvl->end_screen = ft_calloc(sizeof(t_sprite), 1);
	lvl->path_grid = ft_calloc(lvl->map_size.x
			* lvl->map_size.y, sizeof(t_path_case));
	lvl->dist_table = ft_calloc(lvl->map_size.x
			* lvl->map_size.y, sizeof(int));
	if (!(lvl->canvas && lvl->player1 && lvl->arrow && lvl->ui
			&& lvl->end_screen && lvl->path_grid && lvl->dist_table))
		exit_game(game, "Error\nAllocation error.\n");
	lvl->arrow->image_id = e_arrow;
	lvl->ui->image_id = e_ui;
	lvl->end_screen->image_id = e_end_screen;
	btmlx_get_addr(lvl->arrow, lvl->images[e_arrow]);
	btmlx_get_addr(lvl->end_screen, lvl->images[e_end_screen]);
	btmlx_get_addr(lvl->ui, lvl->images[e_ui]);
	init_lvl_base2(game);
}
