/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:07 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/05 03:19:38 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	press_on_w(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += -1;
	else
		game->lvl->player->dir.y += 1;
	
}

void	press_on_a(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += -1;
	else
		game->lvl->player->dir.x += 1;
}

void	press_on_s(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.y += 1;
	else
		game->lvl->player->dir.y += -1;
}

void	press_on_d(t_game *game, int is_release)
{
	if (!is_release)
		game->lvl->player->dir.x += 1;
	else
		game->lvl->player->dir.x += -1;
}

void	press_on_esc(t_game *game, int status)
{
	(void)game;
	exit(status);
}