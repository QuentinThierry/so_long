/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_choose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:20:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/24 16:14:55 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static enum e_img_id	_get_map_info(char *map, int chunk)
{
	if (map[chunk] == '0')
		return (e_ground0);
	if (map[chunk] == '1')
		return (e_wall0_0);
	if (map[chunk] == 'E')
		return (e_exit);
	if (map[chunk] == 'C')
		return (e_collec0);
	return (e_ground0);
}

static enum e_img_id	_choose_ground(void)
{
	int	rng;

	rng = rand() % 100;
	if (rng < 5)
		return (e_ground3);
	if (rng < 15)
		return (e_ground2);
	if (rng < 50)
		return (e_ground1);
	return (e_ground0);
}

static enum e_img_id	_choose_wall(void)
{
	int	rng;

	rng = rand() % 100;
	if (rng < 50)
		return (e_wall1_0);
	return (e_wall0_0);
}

static enum e_img_id	_choose_collec(void)
{
	return (e_collec0);
}

enum e_img_id	choose_image(char *map, int chunk)
{
	enum e_img_id	id;

	id = _get_map_info(map, chunk);
	if (id == e_ground0)
		return (_choose_ground());
	if (id == e_wall0_0)
		return (_choose_wall());
	if (id == e_exit)
		return (e_exit);
	if (id == e_collec0)
		return (_choose_collec());
	return (e_ground0);
}
