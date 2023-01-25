/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:18:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/25 16:11:22 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_colliding(t_collider *collider1, t_collider *collider2)
{
	if (
		collider1->min.x < collider2->max.x &&
		collider1->max.x > collider2->min.x &&
		collider1->min.y < collider2->max.y &&
		collider1->max.y > collider2->min.y
		)
		return (1);
	return (0);
}

t_collider *check_player_collision(t_level *lvl)
{
	int	i;

	i = 0;
	while (lvl->stat_collision[i].id != -1)
	{
		if (is_colliding(lvl->player->collider, &lvl->stat_collision[i]))
			return (&lvl->stat_collision[i]);
		++i;
	}
	return (NULL);
}
