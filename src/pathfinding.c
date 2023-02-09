/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:52:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/09 21:52:59 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	_get_new_case(int pos, int mapx, int dir)
{
	if (dir == 0)
		return (pos + 1);
	if (dir == 1)
		return (pos - 1);
	if (dir == 2)
		return (pos + mapx);
	if (dir == 3)
		return (pos - mapx);
	return (-1);
}

static int	_get_min(t_level *lvl, int nb_cases)
{
	int				i;
	int	min;
	int				min_pos;

	i = 0;
	min = 0;
	min_pos = -1;
	while (i < nb_cases)
	{
		if ((lvl->path_grid[i].tot < min || min == 0) && lvl->path_grid[i].tot > 0
			&& !lvl->path_grid[i].has_been_check)
		{
			lvl->path_grid[i].has_been_check = 1;
			min = lvl->path_grid[i].tot;
			min_pos = i;
		}
		++i;
	}
	return (min_pos);
}

static int	_get_max(t_level *lvl, int nb_cases)
{
	int				i;
	int	max;
	int				max_pos;

	i = 0;
	max = 0;
	max_pos = -1;
	while (i < nb_cases)
	{
		if (lvl->path_grid[i].tot > max)
		{
			max = lvl->path_grid[i].tot;
			max_pos = i;
		}
		++i;
	}
	return (max_pos);
}

static int	_fill_the_four(t_level *lvl, int pos)
{
	int i;
	int	index;
	int	is_end;

	i = 0;
	is_end = 0;
	while (i < 4)
	{
		index = _get_new_case(pos, lvl->map_size.x, i);
		if (lvl->map[index] == '1' && ++i)
		{
			lvl->path_grid[index] = (t_path_case){-2, -2, -2, 1};
			is_end++;
			continue ;
		}
		lvl->path_grid[index].dst_start = lvl->path_grid[pos].dst_start + 1;
		lvl->path_grid[index].dst_end =
				distance(lvl->canvas->chunks[index].pos,
				lvl->canvas->chunks[lvl->exit_chunk].pos);
		lvl->path_grid[index].tot = lvl->path_grid[index].dst_start
				+ lvl->path_grid[index].dst_end;
		if (lvl->path_grid[index].dst_end == 0)
			return (index);
		++i;
	}
	if (is_end == 3)
		lvl->path_grid[pos] = (t_path_case){-2, -2, -2, 1};
	return (0);
}


void	a_star(t_game *game, t_player *player)
{
	int	start;
	int	nb_cases;
	int	min;
	int	end;
	int	max;

	end = 0;
	nb_cases = game->lvl->map_size.x * game->lvl->map_size.y;
	start = pos_to_chunk(game->lvl, player->pos->x, player->pos->y);
	ft_bzero(game->lvl->path_grid, nb_cases * sizeof(t_path_case));
	game->lvl->path_grid[start].dst_start = 0;
	game->lvl->path_grid[start].dst_end = distance(game->lvl->canvas->chunks[start].pos,
			game->lvl->canvas->chunks[game->lvl->exit_chunk].pos);
	game->lvl->path_grid[start].tot = game->lvl->path_grid[start].dst_start
			+ game->lvl->path_grid[start].dst_end;
	min = 0;
	max = 1;
	while (!end)
	{
		if (min == -1)
			break;
		min = _get_min(game->lvl, nb_cases);
		max = _get_max(game->lvl, nb_cases);
		end = _fill_the_four(game->lvl, min);
		game->lvl->canvas->chunks_to_redraw[min] = 1;
	}
	printf("ferme ? : %d\n", end);
}
