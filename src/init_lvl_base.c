/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lvl_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:45:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 22:19:39 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_init_canvas(t_level *lvl)
{
	lvl->canvas->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->canvas->sprite->image_id = e_canvas;
	btmlx_get_addr(lvl->canvas->sprite, lvl->images[e_canvas]);
}

static void	_init_camera(t_level *lvl)
{
	lvl->cam = ft_calloc(sizeof(t_camera), 1);
	lvl->cam->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->cam->sprite->pos = (t_vector2){0, 0};
	lvl->cam->pos = &lvl->cam->sprite->pos;
	lvl->cam->size = &lvl->cam->sprite->size;
	lvl->cam->exact_pos = (t_fvector2){lvl->cam->pos->y,
		lvl->cam->pos->y};
	lvl->cam->dir = (t_fvector2){0, 0};
	lvl->cam->sprite->image_id = e_camera;
	btmlx_get_addr(lvl->cam->sprite, lvl->images[e_camera]);
	lvl->cam->is_cam_lock = 1;
}

static void	_init_background(t_level *lvl)
{
	lvl->background = ft_calloc(sizeof(t_sprite), 1);
	lvl->background->pos = (t_vector2){0, 0};
	lvl->background->image_id = e_background;
	btmlx_get_addr(lvl->background, lvl->images[e_background]);
}

static void	_init_player1(t_level *lvl)
{
	lvl->player1->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->player1->collider = ft_calloc(sizeof(t_collider), 1);
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

void	init_player2(t_level *lvl)
{
	lvl->player2 = ft_calloc(sizeof(t_player), 1);
	lvl->player2->sprite = ft_calloc(sizeof(t_sprite), 1);
	lvl->player2->collider = ft_calloc(sizeof(t_collider), 1);
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

void	init_lvl_base(t_level *lvl)
{
	lvl->canvas = ft_calloc(sizeof(t_canvas), 1);
	lvl->player1 = ft_calloc(sizeof(t_player), 1);
	lvl->arrow = ft_calloc(sizeof(t_sprite), 1);
	lvl->arrow->image_id = e_arrow;
	btmlx_get_addr(lvl->arrow, lvl->images[e_arrow]);
	lvl->nb_collec = 0;
	lvl->max_collec = 0;
	lvl->nb_move = 0;
	lvl->path_grid = ft_calloc(lvl->map_size.x
			* lvl->map_size.y, sizeof(t_path_case));
	lvl->dist_table = ft_calloc(lvl->map_size.x
			* lvl->map_size.y, sizeof(int));
	if (ISDEBUG)
	{
		lvl->debug_sprite = ft_calloc(sizeof(t_sprite), 1);
		lvl->debug_sprite->image_id = e_debug;
		btmlx_get_addr(lvl->debug_sprite, lvl->images[e_debug]);
		lvl->debug_tile_sprite = ft_calloc(sizeof(t_sprite), 1);
		lvl->debug_tile_sprite->image_id = e_debug_tile;
		btmlx_get_addr(lvl->debug_tile_sprite, lvl->images[e_debug_tile]);
	}
	_init_canvas(lvl);
	_init_camera(lvl);
	_init_player1(lvl);
	_init_background(lvl);
}
