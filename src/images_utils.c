/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:37:09 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/29 20:39:20 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	allocate_picts(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_VARIANT)
	{
		game->lvl->images[e_ground][i] = malloc(sizeof(t_pict));
		game->lvl->images[e_wall][i] = malloc(sizeof(t_pict));
		game->lvl->images[e_collec][i] = malloc(sizeof(t_pict));
		game->lvl->images[e_exit][i] = malloc(sizeof(t_pict));
		if (!game->lvl->images[e_ground][i] || !game->lvl->images[e_wall][i]
		|| game->lvl->images[e_collec][i] || !game->lvl->images[e_exit][i])
			return (0);
	}
	return (1);
}
