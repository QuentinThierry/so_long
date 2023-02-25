/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:25:50 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 16:55:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static t_enemy	*_instantiate_enemy(t_img **images, int id)
{
	t_enemy	*enemy;

	enemy = ft_calloc(sizeof(t_enemy), 1);
	if (!enemy)
		return (NULL);
	enemy->id = id;
	enemy->is_triggered = 0;
	enemy->sprite = ft_calloc(sizeof(t_sprite), 1);
	if (!enemy->sprite)
		return (free(enemy), NULL);
	enemy->sprite->image_id = e_enemy_idle_0_0;
	enemy->anim_time = (struct timeval){0, 0};
	btmlx_get_addr(enemy->sprite, images[e_enemy_idle_0_0]);
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
	enemy->is_look_left = 1;
	return (enemy);
}

static int	get_nb_enemies(t_level *lvl)
{
	int	i;
	int	nb_enemies;

	nb_enemies = 0;
	i = 0;
	while (i < lvl->canvas->nb_chunks.y * lvl->canvas->nb_chunks.x)
	{
		if (lvl->map[i] == 'S')
			nb_enemies++;
		i++;
	}
	return (nb_enemies);
}

void	error_free_enemies(t_enemy ***enemies, int i)
{
	while (i >= 0)
	{
		free((*enemies)[i]->sprite);
		free((*enemies)[i]->collider);
		free((*enemies)[i]);
		(*enemies)[i] = NULL;
		i--;
	}
	free((*enemies));
	(*enemies) = NULL;
}

int	init_enemies(t_level *lvl)
{
	int	i;
	int	j;
	int	nb_enemies;

	nb_enemies = get_nb_enemies(lvl);
	lvl->enemies = ft_calloc(sizeof(t_enemy *), (nb_enemies + 1));
	if (!lvl->enemies)
		return (0);
	i = -1;
	j = 0;
	while (++i < lvl->canvas->nb_chunks.y * lvl->canvas->nb_chunks.x)
	{
		if (lvl->map[i] != 'S')
			continue ;
		lvl->enemies[j] = _instantiate_enemy(lvl->images, j);
		if (!lvl->enemies[j])
			return (error_free_enemies(&lvl->enemies, j - 1), 0);
		*lvl->enemies[j]->pos = lvl->canvas->chunks[i].pos;
		lvl->enemies[j]->exact_pos = (t_fvector2)
		{lvl->enemies[j]->pos->x, lvl->enemies[j]->pos->y};
		lvl->enemies[j]->dir = (t_fvector2){1, 1};
		j++;
	}
	return (1);
}
