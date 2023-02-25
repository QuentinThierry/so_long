/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:07 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:35:39 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static enum e_key_map	_get_key2(int key)
{
	if (key == KEY_UA)
		return (e_UA);
	if (key == KEY_RA)
		return (e_RA);
	if (key == KEY_DA)
		return (e_DA);
	if (key == KEY_8)
		return (e_8);
	if (key == KEY_4)
		return (e_4);
	if (key == KEY_5)
		return (e_5);
	if (key == KEY_6)
		return (e_6);
	if (key == KEY_ESC)
		return (e_ESC);
	if (key == KEY_ENTER)
		return (e_ENTER);
	return (NB_KEYS);
}

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
	if (key == KEY_P)
		return (e_P);
	if (key == KEY_L)
		return (e_L);
	if (key == KEY_LA)
		return (e_LA);
	return (_get_key2(key));
}

int	press_key(int key, t_game *game)
{
	enum e_key_map	e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 0);
	return (0);
}

int	release_key(int key, t_game *game)
{
	enum e_key_map	e_key;

	e_key = get_key(key);
	if (e_key < NB_KEYS)
		game->press_on_key[e_key](game, 1);
	return (0);
}

void	press_on_esc(t_game *game, int is_release)
{
	(void)game;
	(void)is_release;
	exit_game(game, NULL);
}
