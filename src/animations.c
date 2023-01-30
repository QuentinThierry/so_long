/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:42:19 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 21:04:57 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


static void	animate_player(t_level *lvl)
{
	if (lvl->sprites[e_player]->current_var >= 4)
		lvl->sprites[e_player]->current_var = 0;
	else
		lvl->sprites[e_player]->current_var++;
}

// static void	calculate_ground(t_level *lvl)
// {
	
// }

void	calculate_animations(t_game *game)
{
	// animate_player(game->lvl);
	// // calculate_ground(game->lvl);
	// if (game->fps % 2 == 0)
	// {
	// 	game->lvl->canvas->chunks[40].variant = 0;
	// 	game->lvl->canvas->chunks_to_redraw[40] = 1;
	// }
	// else if (game->fps % 1 == 0)
	// {
	// 	game->lvl->canvas->chunks[40].variant = 3;
	// 	game->lvl->canvas->chunks_to_redraw[40] = 1;
	// }
}
