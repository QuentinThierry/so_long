/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:31:32 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:32:37 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_col_exit(t_game *game)
{
	if ((is_colliding(game->lvl->player1->collider, game->lvl->exit_col)
			&& game->lvl->nb_collec >= game->lvl->max_collec)
		&& (!game->lvl->player2
			|| (is_colliding(game->lvl->player2->collider, game->lvl->exit_col)
				&& game->lvl->nb_collec >= game->lvl->max_collec)))
			game->is_end = END_WIN;
}
