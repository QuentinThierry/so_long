/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lvl_base2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:07:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:09:18 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_canvas(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->canvas->sprite = ft_calloc(sizeof(t_sprite), 1);
	if (!lvl->canvas->sprite)
		exit_game(game, "Error\nAllocation error.\n");
	lvl->canvas->sprite->image_id = e_canvas;
	btmlx_get_addr(lvl->canvas->sprite, lvl->images[e_canvas]);
}

void	init_camera(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->cam = ft_calloc(sizeof(t_camera), 1);
	if (!lvl->cam)
		exit_game(game, "Error\nAllocation error.\n");
	lvl->cam->sprite = ft_calloc(sizeof(t_sprite), 1);
	if (!lvl->cam->sprite)
		exit_game(game, "Error\nAllocation error.\n");
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

void	init_background(t_game *game)
{
	t_level	*lvl;

	lvl = game->lvl;
	lvl->background = ft_calloc(sizeof(t_sprite), 1);
	if (!lvl->background)
		exit_game(game, "Error\nAllocation error.\n");
	lvl->background->pos = (t_vector2){0, 0};
	lvl->background->image_id = e_background;
	btmlx_get_addr(lvl->background, lvl->images[e_background]);
}
