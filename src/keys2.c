/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:34:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:35:51 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	press_on_w(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player1->dir.y += -1;
	else
		game->lvl->player1->dir.y += 1;
}

void	press_on_a(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player1->dir.x += -1;
	else
		game->lvl->player1->dir.x += 1;
}

void	press_on_s(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player1->dir.y += 1;
	else
		game->lvl->player1->dir.y += -1;
}

void	press_on_d(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player1->dir.x += 1;
	else
		game->lvl->player1->dir.x += -1;
}

void	press_on_p(t_game *game, int is_release)
{
	if (!is_release && game->lvl->is_animating_cam)
		game->lvl->start_time.tv_sec -= CAM_ANIM_TIME_SEC + 1;
}
