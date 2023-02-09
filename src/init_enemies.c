/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:25:50 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/09 19:41:04 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static t_enemy	*_instantiate_enemy(t_img **images, int id)
{
	t_enemy *enemy;

	enemy = ft_calloc(sizeof(t_enemy), 1);
	if (!enemy)
		return (NULL);
	enemy->id = id;
	enemy->is_triggered = 0;
	enemy->sprite = ft_calloc(sizeof(t_sprite), 1);
	if (!enemy->sprite)
		return (free(enemy), NULL);
	enemy->sprite->image_id = e_enemy_0_0;
	btmlx_get_addr(enemy->sprite, images[e_enemy_0_0]);
	enemy->pos = &enemy->sprite->pos;
	enemy->size = &enemy->sprite->size;
	enemy->collider = ft_calloc(sizeof(t_collider), 1);
	if (!enemy->collider)
		return (free(enemy->sprite), free(enemy), NULL);
	enemy->collider->id = id;
	enemy->collider->has_been_triggered = 0;
	enemy->collider->image_id = &enemy->sprite->image_id;
	enemy->collider->pos = enemy->pos;
	enemy->collider->size = enemy->size;
	return (enemy);
}

int	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	nb_enemies;

	i = 0;
	nb_enemies = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		if (game->lvl->map[i] == 'G')
			nb_enemies++;
		i++;
	}
	game->lvl->enemies = ft_calloc(sizeof(t_enemy *), (nb_enemies + 1));
	if (!game->lvl->enemies)
		return (0);
	i = 0;
	j = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		if (game->lvl->map[i] == 'G')
		{
			game->lvl->enemies[j] = _instantiate_enemy(game->lvl->images, j);
			if (!game->lvl->enemies[j])
				return (0);
			*game->lvl->enemies[j]->pos = game->lvl->canvas->chunks[i].pos;
			game->lvl->enemies[j]->exact_pos = (t_fvector2)
			{
				game->lvl->enemies[j]->pos->x,
				game->lvl->enemies[j]->pos->y
			};
			game->lvl->enemies[j]->dir = (t_fvector2){1, 1};
			j++;
		}
		i++;
	}
	game->lvl->enemies[nb_enemies] = NULL;
	return (1);
}