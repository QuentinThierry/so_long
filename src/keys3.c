/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:34:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 19:51:27 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	press_on_l(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->cam->is_cam_lock *= -1;
}

void	press_on_la(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.x += -1;
		else
			game->lvl->player2->dir.x += 1;
	}
}

void	press_on_ua(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.y += -1;
		else
			game->lvl->player2->dir.y += 1;
	}
}

void	press_on_da(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.y += 1;
		else
			game->lvl->player2->dir.y += -1;
	}
}

void	press_on_ra(t_game *game, int is_release)
{
	if (game->lvl->player2)
	{
		if (!is_release)
			game->lvl->player2->dir.x += 1;
		else
			game->lvl->player2->dir.x += -1;
	}
}
