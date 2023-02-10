/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:52:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/10 02:42:20 by qthierry         ###   ########.fr       */
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
			min = lvl->path_grid[i].tot;
			min_pos = i;
		}
		++i;
	}
	if (min_pos > -1)
		lvl->path_grid[min_pos].has_been_check = 1;
	return (min_pos);
}

inline static int	_is_valid(t_level *lvl, int pos)
{
	return (pos >= 0 && pos < lvl->map_size.x * lvl->map_size.x);
}

static int	_fill_the_four(t_level *lvl, int pos)
{
	int i;
	int	index;

	i = 0;
	while (i < 4)
	{
		index = _get_new_case(pos, lvl->map_size.x, i);
		if (!_is_valid(lvl, index) && ++i)
			continue;
		if (lvl->map[index] == '1' && ++i)
		{
			lvl->path_grid[index] = (t_path_case){-2, -2, -2, 1};
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
	return (0);
}

void	a_star(t_game *game, t_player *player)
{
	int	start;
	int	nb_cases;
	int	min;
	int	end;

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
	while (!end)
	{
		if (min == -1)
			break;
		min = _get_min(game->lvl, nb_cases);
		end = _fill_the_four(game->lvl, min);
		if (ISDEBUG && min > -1)
			game->lvl->canvas->chunks_to_redraw[min] = 1;
	}
}
