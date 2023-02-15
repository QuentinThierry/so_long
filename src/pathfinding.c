/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:52:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/15 21:44:25 by qthierry         ###   ########.fr       */
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
	if (min > -1)
		lvl->path_grid[min_pos].has_been_check = 1;
	return (min_pos);
}

static int	_fill_the_four(t_level *lvl, int pos, int end_chunk, char *path_map)
{
	int i;
	int	index;

	i = 0;
	while (i < 4)
	{
		index = _get_new_case(pos, lvl->map_size.x, i);
		if (!(pos >= 0 && pos < lvl->map_size.x * lvl->map_size.x) && ++i)
			continue ;
		if (lvl->map[index] == '1' && ++i)
		{
			lvl->path_grid[index] = (t_path_case){-2, -2, -2, 0, -1};
			continue ;
		}
		if (lvl->path_grid[index].dst_start &&
			lvl->path_grid[index].dst_start < lvl->path_grid[pos].dst_start)
		{
			i++;
			continue ;
		}
		lvl->path_grid[index].dst_start = lvl->path_grid[pos].dst_start + 1;
		lvl->path_grid[index].dst_end =
				(sqrdistance(lvl->canvas->chunks[index].pos,
				lvl->canvas->chunks[end_chunk].pos) + 1) / SIZE_CHUNK;
		lvl->path_grid[index].tot = lvl->path_grid[index].dst_start
				+ lvl->path_grid[index].dst_end;
		if (lvl->path_grid[pos].parent != index)
			lvl->path_grid[index].parent = pos;
		if (lvl->path_grid[index].dst_end == 0 || (path_map && path_map[i] == '1'))
			return (index);
		++i;
	}
	return (0);
}

void	_fill_map(t_path_case *path_grid, char **map)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(*map);
	while (i < size)
	{
		if (path_grid[i].has_been_check)
			(*map)[i] = '1';
		i++;
	}
}

void	a_star(t_game *game, t_vector2 src, t_vector2 dest, char **path_map)
{
	int	start_chunk;
	int	end_chunk;
	int	nb_cases;
	int	min;
	int	end;

	end = 0;
	nb_cases = game->lvl->map_size.x * game->lvl->map_size.y;
	start_chunk = pos_to_chunk(game->lvl, src.x, src.y);
	end_chunk = pos_to_chunk(game->lvl, dest.x, dest.y);
	ft_bzero(game->lvl->path_grid, nb_cases * sizeof(t_path_case));
	game->lvl->path_grid[start_chunk].dst_end = sqrdistance(game->lvl->canvas->chunks[start_chunk].pos,
			game->lvl->canvas->chunks[end_chunk].pos) / SIZE_CHUNK;
	if (game->lvl->path_grid[start_chunk].dst_end == 0)
		return ;
	game->lvl->path_grid[start_chunk].tot = game->lvl->path_grid[start_chunk].dst_end;
	min = 0;
	while (!end)
	{
		if (min == -1)
			break;
		min = _get_min(game->lvl, nb_cases);
		if (path_map)
			end = _fill_the_four(game->lvl, min, end_chunk, *path_map);
		else
			end = _fill_the_four(game->lvl, min, end_chunk, NULL);
	}
	if (ISDEBUG && min > -1)
		draw_shortest_path(game->lvl, end);
	if (path_map)
		_fill_map(game->lvl->path_grid, path_map);
}

// void	print_parents(t_level *lvl, int i)
// {
// 	// printf("i : %d\n", i);
// 	if (lvl->path_grid[i].parent != 0)
// 	{
// 		// (*cmp)++;
// 		print_parents(lvl, lvl->path_grid[i].parent);
// 		if (ISDEBUG)
// 			lvl->canvas->chunks_to_redraw[i] = 1;
// 		// printf("path : %d\n", lvl->path_grid[i].parent);
// 	}
// }

// void	print_path(t_game *game)
// {
// 	int i;

// 	i = 0;
// 	while (i < game->lvl->map_size.x * game->lvl->map_size.y)
// 	{
// 		if (game->lvl->path_grid[i].has_been_check)
// 			printf("\e[102m%3c \e[0m", 'I');
// 		else
// 			printf("%3c ", '0');
// 		if (i % game->lvl->map_size.x == game->lvl->map_size.x - 1)
// 			printf("\n");
// 		i++;
// 	}
// 	printf("\n");
// }