/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:16:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/15 21:44:16 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_valid_path(t_game *game)
{
	char	*map_cpy;
	size_t	size_map;

	map_cpy = ft_strdup(game->lvl->map);
	if (!map_cpy)
		return (-1);
	size_map = ft_strlen(map_cpy);
	ft_memset(map_cpy, '0', size_map);
	a_star(game, *game->lvl->player1->pos, game->lvl->canvas->chunks[36].pos, &map_cpy);
	
	// add collectibles path to the end, or a 1

	printf("map : %s\n", map_cpy);
	return (0);
}
