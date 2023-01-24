/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:04:49 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/24 22:41:19 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// last index is empty and has -1 id
// id 0 is player
static int	create_static_collisions(t_level *lvl)
{
	int	nb_walls;
	int	i;
	int	j;

	i = 0;
	nb_walls = 0;
	while (i < lvl->map_size.x * lvl->map_size.y)
	{
		if (lvl->map[i] == '1')
			nb_walls++;
		++i;
	}
	lvl->stat_collision = malloc(sizeof(t_collider) * (nb_walls + 1));
	if (!lvl->stat_collision)
		return (0);
	i = 0;
	j = 0;
	while (i < lvl->map_size.x * lvl->map_size.y)
	{
		if (lvl->map[i] == '1')
		{
			lvl->stat_collision[j].id = j + 1;
			lvl->stat_collision[j].pos = lvl->canvas->chunks[i].pos;
			lvl->stat_collision[j].size = lvl->canvas->chunks[i].size;
			lvl->stat_collision[j].pos_size = (t_vector2)
			{
				lvl->canvas->chunks[i].pos.x + lvl->canvas->chunks[i].size.x,
				lvl->canvas->chunks[i].pos.y + lvl->canvas->chunks[i].size.y
			};
			++j;
		}
		++i;
	}
	lvl->stat_collision[j].id = -1;
	return (1);
}

static int	create_dynamic_collisions(t_level *lvl)
{
	(void)lvl;


	return (1);
}


int	init_collisions(t_level *lvl)
{
	if (create_static_collisions(lvl) == 0)
		return (0);
	if (create_dynamic_collisions(lvl) == 0)
		return (0);
	return (1);
}
