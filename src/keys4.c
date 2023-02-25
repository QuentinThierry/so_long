/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:35:19 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:35:45 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	press_on_8(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.y += -1;
		else
			game->lvl->player2->dir.y += 1;
	}
}

void	press_on_4(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.x += -1;
		else
			game->lvl->player2->dir.x += 1;
	}
}

void	press_on_5(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.y += 1;
		else
			game->lvl->player2->dir.y += -1;
	}
}

void	press_on_6(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.x += 1;
		else
			game->lvl->player2->dir.x += -1;
	}
}

void	press_on_enter(t_game *game, int is_release)
{
	(void)is_release;
	if (!game->lvl->player2)
		init_player2(game);
}
