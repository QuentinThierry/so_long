/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:04:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 22:38:53 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	count_on_map(t_level *lvl, char c)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < lvl->map_size.x * lvl->map_size.y)
	{
		if (lvl->map[i] == c)
			res++;
		++i;
	}
	return (res);
}

static int	create_wall_colliders(t_level *lvl)
{
	int	nb_walls;
	int	i;
	int	j;

	nb_walls = count_on_map(lvl, '1');
	lvl->wall_col = ft_calloc(sizeof(t_collider), (nb_walls + 1));
	if (!lvl->wall_col)
		return (0);
	i = -1;
	j = 0;
	while (++i < lvl->map_size.x * lvl->map_size.y)
	{
		if (lvl->map[i] == '1')
		{
			lvl->wall_col[j].id = j + 1;
			lvl->wall_col[j].pos = &lvl->canvas->chunks[i].pos;
			lvl->wall_col[j].size = &lvl->canvas->chunks[i].size;
			lvl->wall_col[j].image_id = &lvl->canvas->chunks[i].image_id;
			lvl->wall_col[j].has_been_triggered = 0;
			++j;
		}
	}
	lvl->wall_col[j].id = -1;
	return (1);
}

static int	create_collec_colliders(t_level *lvl)
{
	int	nb_triggers;
	int	i;
	int	j;

	nb_triggers = count_on_map(lvl, 'C');
	lvl->collec_col = ft_calloc(sizeof(t_collider), (nb_triggers + 1));
	if (!lvl->collec_col)
		return (0);
	i = -1;
	j = 0;
	while (++i < lvl->map_size.x * lvl->map_size.y)
	{
		if (lvl->map[i] == 'C')
		{
			lvl->collec_col[j].id = j + 1;
			lvl->collec_col[j].pos = &lvl->canvas->chunks[i].pos;
			lvl->collec_col[j].size = &lvl->canvas->chunks[i].size;
			lvl->collec_col[j].image_id = &lvl->canvas->chunks[i].image_id;
			lvl->collec_col[j].has_been_triggered = 0;
			++j;
		}
	}
	lvl->collec_col[j].id = -1;
	return (1);
}

static int	create_exit_collider(t_level *lvl)
{
	int	exit_chunk;

	lvl->exit_col = ft_calloc(sizeof(t_collider), 1);
	if (!lvl->exit_col)
		return (0);
	exit_chunk = find_exit_chunk(lvl->map);
	lvl->exit_col->id = 0;
	lvl->exit_col->pos = &lvl->canvas->chunks[exit_chunk].pos;
	lvl->exit_col->size = &lvl->canvas->chunks[exit_chunk].size;
	lvl->exit_col->image_id = &lvl->canvas->chunks[exit_chunk].image_id;
	lvl->exit_col->has_been_triggered = 0;
	return (1);
}

int	init_collisions(t_level *lvl)
{
	if (!create_wall_colliders(lvl))
		return (0);
	if (!create_collec_colliders(lvl))
		return (0);
	if (!create_exit_collider(lvl))
		return (0);
	return (1);
}
