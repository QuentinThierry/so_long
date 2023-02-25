/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:52:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:12:52 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	_fill_map(t_path_case *path_grid, char **map)
{
	int	i;

	i = 0;
	while ((*map)[i])
	{
		if (path_grid[i].has_been_check)
			(*map)[i] = '1';
		i++;
	}
}

int	a_star(t_game *game, t_vector2 src, char **path_map)
{
	int	start_chunk;
	int	nb_cases;
	int	end;

	nb_cases = game->lvl->map_size.x * game->lvl->map_size.y;
	start_chunk = pos_to_chunk(game->lvl, src.x, src.y);
	ft_bzero(game->lvl->path_grid, nb_cases * sizeof(t_path_case));
	if (game->lvl->dist_table[start_chunk] == 0)
		return (1);
	game->lvl->path_grid[start_chunk].tot = game->lvl->dist_table[start_chunk];
	end = iterate_on_map(game->lvl, nb_cases, path_map);
	if (!end)
		return (0);
	if (ISDEBUG)
		draw_shortest_path(game->lvl, end);
	if (path_map)
		_fill_map(game->lvl->path_grid, path_map);
	return (end);
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

// void	_print_map2(int map_size, int mapx, char *map)
// {
// 	int	i;

// 	i = 0;
// 	printf("\n");
// 	while (i < map_size)
// 	{
// 		if (map[i] == '1')
// 			printf("\e[108m");
// 		printf("%3d ", map[i]);
// 		if (i % mapx == mapx - 1)
// 			printf("\n");
// 		if (map[i] == '1')
// 			printf("\e[0m");
// 		i++;
// 	}
// }

// static void	_print_path(t_game *game)
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
