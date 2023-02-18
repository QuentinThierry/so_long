/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:16:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 22:43:01 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_valid_path(t_game *game)
{
	char		*map_cpy;
	size_t		size_map;
	t_chunk		*chunks;
	t_player	*player;
	size_t		i;

	size_map = game->lvl->map_size.x * game->lvl->map_size.y;
	map_cpy = ft_strdup(game->lvl->map);
	if (!map_cpy)
		return (-1);
	chunks = game->lvl->canvas->chunks;
	player = game->lvl->player1;
	if (!a_star(game, *player->pos, &map_cpy))
		return (free(map_cpy), 0);
	i = 0;
	while (i < size_map)
	{
		if (game->lvl->map[i] == 'C'
			&& !a_star(game, chunks[i].pos, &map_cpy))
			return (free(map_cpy), 0);
		i++;
	}
	free(map_cpy);
	return (1);
}

// void	_print_map(int map_size, int mapx, char *map)
// {
// 	int	i;

// 	i = 0;
// 	printf("\n");
// 	while (i < map_size)
// 	{
// 		if (map[i] == '1')
// 			printf("\e[105m");
// 		printf("%3d ", map[i]);
// 		if (i % mapx == mapx - 1)
// 			printf("\n");
// 		if (map[i] == '1')
// 			printf("\e[0m");
// 		i++;
// 	}
// }
