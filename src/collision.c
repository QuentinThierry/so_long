/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:18:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/14 02:01:57 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_colliding(t_collider *collider1, t_collider *collider2)
{
	t_vector2	collider1_max;
	t_vector2	collider2_max;

	collider1_max.x = collider1->pos->x + collider1->size->x;
	collider1_max.y = collider1->pos->y + collider1->size->y;
	collider2_max.x = collider2->pos->x + collider2->size->x;
	collider2_max.y = collider2->pos->y + collider2->size->y;
	if (
		collider1->pos->x < collider2_max.x &&
		collider1_max.x > collider2->pos->x &&
		collider1->pos->y < collider2_max.y &&
		collider1_max.y > collider2->pos->y
		)
		return (1);
	return (0);
}


void	collide_on_collec(t_game *game, t_collider *collider)
{
	game->lvl->nb_collec++;
	printf("collected : (%d/%d) !\n", game->lvl->nb_collec, game->lvl->max_collec);
	*collider->image_id = e_collec3_0;
	collider->has_been_triggered = 1;
}

void	check_col_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->enemies[i])
	{
		if (is_inside_load_range(game, *game->lvl->enemies[i]->pos)
				&& is_colliding(game->lvl->enemies[i]->collider,
			game->lvl->player1->collider))
		{
			printf("Player 1 is dead\n");
			break;
		}
		if (game->lvl->player2)
		{
			if (is_inside_load_range(game, *game->lvl->enemies[i]->pos)
				&& is_colliding(game->lvl->enemies[i]->collider,
			game->lvl->player2->collider))
			{
				printf("Player 2 is dead\n");
				break;
			}
		}
		i++;
	}
}

void	check_col_exit(t_game *game)
{
	if ((is_colliding(game->lvl->player1->collider, game->lvl->exit_col)
		&& game->lvl->nb_collec >= game->lvl->max_collec)
		&& (!game->lvl->player2
		|| (is_colliding(game->lvl->player2->collider, game->lvl->exit_col)
		&& game->lvl->nb_collec >= game->lvl->max_collec)))
		exit_game(game);
}

void	check_col_collectible(t_game *game)
{
	int	i;

	i = 0;
	while (game->lvl->collec_col[i].id != -1)
	{
		if (is_colliding(game->lvl->player1->collider, &game->lvl->collec_col[i])
			&& game->lvl->collec_col[i].has_been_triggered == 0)
			collide_on_collec(game, &game->lvl->collec_col[i]);
		++i;
	}
	if (!game->lvl->player2)
		return ;
	i = 0;
	while (game->lvl->collec_col[i].id != -1)
	{
		if (is_colliding(game->lvl->player2->collider, &game->lvl->collec_col[i])
			&& game->lvl->collec_col[i].has_been_triggered == 0)
			collide_on_collec(game, &game->lvl->collec_col[i]);
		++i;
	}
}

t_collider	*check_wall_collision(t_level *lvl, t_collider *src)
{
	int	i;

	i = 0;
	while (lvl->wall_col[i].id != -1)
	{
		if (is_colliding(src, &lvl->wall_col[i]))
			return (&lvl->wall_col[i]);
		++i;
	}
	return (NULL);
}
