/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lvl_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:45:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/11 21:37:49 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_init_canvas(t_game *game)
{
	game->lvl->canvas->sprite = ft_calloc(sizeof(t_sprite), 1);
	game->lvl->canvas->sprite->image_id = e_canvas;
	game->lvl->canvas->origin = (t_vector2){0, 0};
	btmlx_get_addr(game->lvl->canvas->sprite, game->lvl->images[e_canvas]);
}

static void	_init_camera(t_game *game)
{
	game->lvl->cam = ft_calloc(sizeof(t_camera), 1);
	game->lvl->cam->sprite = ft_calloc(sizeof(t_sprite), 1);
	game->lvl->cam->sprite->pos = (t_vector2) {0, 0};
	game->lvl->cam->pos = &game->lvl->cam->sprite->pos;
	game->lvl->cam->size = &game->lvl->cam->sprite->size;
	game->lvl->cam->exact_pos = (t_fvector2){game->lvl->cam->pos->y,
		game->lvl->cam->pos->y};
	game->lvl->cam->dir = (t_fvector2) {0, 0};
	game->lvl->cam->sprite->image_id = e_camera;
	btmlx_get_addr(game->lvl->cam->sprite, game->lvl->images[e_camera]);
	game->lvl->cam->is_cam_lock = 1;
}


static void	_init_background(t_game *game)
{
	game->lvl->background = ft_calloc(sizeof(t_sprite), 1);
	game->lvl->background->pos = (t_vector2) {0, 0};
	game->lvl->background->image_id = e_background;
	btmlx_get_addr(game->lvl->background, game->lvl->images[e_background]);
}

static void	_init_player1(t_game *game)
{
	game->lvl->player1->sprite = ft_calloc(sizeof(t_sprite), 1);
	game->lvl->player1->collider = ft_calloc(sizeof(t_collider), 1);
	game->lvl->player1->collider->id = 0;
	game->lvl->player1->collider->pos = &game->lvl->player1->sprite->pos;
	game->lvl->player1->collider->size = &game->lvl->player1->sprite->size;
	game->lvl->player1->dir = (t_vector2){0, 0};
	game->lvl->player1->is_look_left = 0;
	game->lvl->player1->sprite->image_id = e_player_idle_0_0;
	btmlx_get_addr(game->lvl->player1->sprite, 
			game->lvl->images[e_player_idle_0_0]);
	game->lvl->player1->pos = &game->lvl->player1->sprite->pos;
}

void	init_player2(t_game *game)
{
	game->lvl->player2 = ft_calloc(sizeof(t_player), 1);
	game->lvl->player2->sprite = ft_calloc(sizeof(t_sprite), 1);
	game->lvl->player2->collider = ft_calloc(sizeof(t_collider), 1);
	game->lvl->player2->collider->id = 0;
	game->lvl->player2->collider->pos = &game->lvl->player2->sprite->pos;
	game->lvl->player2->collider->size = &game->lvl->player2->sprite->size;
	game->lvl->player2->dir = (t_vector2){0, 0};
	game->lvl->player2->is_look_left = 0;
	game->lvl->player2->sprite->image_id = e_player_idle_0_0;
	btmlx_get_addr(game->lvl->player2->sprite, 
			game->lvl->images[e_player_idle_0_0]);
	game->lvl->player2->pos = &game->lvl->player2->sprite->pos;
	*game->lvl->player2->pos = *game->lvl->player1->pos;
	game->lvl->player2->exact_pos = 
		(t_fvector2) {game->lvl->player1->pos->x, game->lvl->player1->pos->y};
}

void	init_lvl_base(t_game *game)
{
	game->lvl->canvas = ft_calloc(sizeof(t_canvas), 1);
	game->lvl->player1 = ft_calloc(sizeof(t_player), 1);
	game->lvl->nb_collec = 0;
	game->lvl->max_collec = 0;
	game->lvl->path_grid = ft_calloc(game->lvl->map_size.x *
		game->lvl->map_size.y, sizeof(t_path_case));
	if (ISDEBUG)
	{
		game->lvl->debug_sprite = ft_calloc(sizeof(t_sprite), 1);
		game->lvl->debug_sprite->image_id = e_debug;
		btmlx_get_addr(game->lvl->debug_sprite, game->lvl->images[e_debug]);
		game->lvl->debug_tile_sprite = ft_calloc(sizeof(t_sprite), 1);
		game->lvl->debug_tile_sprite->image_id = e_debug_tile;
		btmlx_get_addr(game->lvl->debug_tile_sprite, game->lvl->images[e_debug_tile]);
	}
	_init_canvas(game);
	_init_camera(game);
	_init_player1(game);
	_init_background(game);
}

