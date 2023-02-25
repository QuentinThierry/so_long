/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:11:56 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:27:08 by qthierry         ###   ########.fr       */
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
	int	min;
	int	min_pos;
	int	i;

	min = __INT_MAX__;
	min_pos = -1;
	i = 0;
	while (i < nb_cases)
	{
		if (!lvl->path_grid[i].has_been_check
			&& lvl->path_grid[i].tot > 0
			&& (lvl->path_grid[i].tot < min))
		{
			min = lvl->path_grid[i].tot;
			min_pos = i;
		}
		i++;
	}
	if (min_pos > -1)
		lvl->path_grid[min_pos].has_been_check = 1;
	return (min_pos);
}

static int	is_valid_index(t_level *lvl, int index, int pos)
{
	if (lvl->map[index] == '1')
	{
		lvl->path_grid[index] = (t_path_case){__INT_MAX__, -2, 0, -1};
		return (0);
	}
	if (lvl->path_grid[index].dst_start
		&& lvl->path_grid[index].dst_start < lvl->path_grid[pos].dst_start)
		return (0);
	return (1);
}

static int	_fill_the_four(t_level *lvl, int pos, char *path_map)
{
	int	i;
	int	index;

	i = 0;
	while (i < 4)
	{
		if (!(pos >= 0 && pos < lvl->map_size.x * lvl->map_size.x) && ++i)
			continue ;
		index = _get_new_case(pos, lvl->map_size.x, i);
		if (!is_valid_index(lvl, index, pos) && ++i)
			continue ;
		lvl->path_grid[index].dst_start = lvl->path_grid[pos].dst_start + 1;
		lvl->path_grid[index].tot = lvl->path_grid[index].dst_start
			+ lvl->dist_table[index];
		if (lvl->path_grid[pos].parent != index)
			lvl->path_grid[index].parent = pos;
		if ((lvl->dist_table[index] == 0)
			|| (path_map && path_map[index] == '1'))
			return (index);
		++i;
	}
	return (0);
}

int	iterate_on_map(t_level *lvl, int nb_cases, char **path_map)
{
	int	end;
	int	min;

	end = 0;
	while (!end)
	{
		min = _get_min(lvl, nb_cases);
		if (min == -1)
			break ;
		if (path_map)
			end = _fill_the_four(lvl, min, *path_map);
		else
			end = _fill_the_four(lvl, min, NULL);
	}
	return (end);
}
