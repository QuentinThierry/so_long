/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:18:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/24 22:40:52 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_colliding(t_collider *collider1, t_collider *collider2)
{
	if (
		collider1->pos.x < collider2->pos_size.x &&
		collider1->pos_size.x > collider2->pos.x &&
		collider1->pos.y < collider2->pos_size.y &&
		collider1->pos_size.y > collider2->pos.y
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
		{
			return (&lvl->stat_collision[i]);
		}
		++i;
	}
	return (NULL);
}
