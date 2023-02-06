/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:07 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/06 20:23:58 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

enum e_key_map	get_key(int key)
{
	if (key == KEY_W)
		return (e_W);
	if (key == KEY_A)
		return (e_A);
	if (key == KEY_S)
		return (e_S);
	if (key == KEY_D)
		return (e_D);
	if (key == KEY_ESC)
		return (e_ESC);
	if (key == KEY_P)
		return (e_P);
	return (NB_KEYS);
}

int	press_key(int key, t_game *game)
{
	enum e_key_map e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 0);
	return (0);
}

int	release_key(int key, t_game *game)
{
	enum e_key_map e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 1);
	return (0);
}

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

void	press_on_p(t_game *game, int is_release)
{
	if (!is_release && game->lvl->is_animating_cam)
		game->lvl->start_time.tv_sec -= CAM_ANIM_TIME_SEC + 1;
}

void	press_on_esc(t_game *game, int status)
{
	(void)game;
	exit(status);
}