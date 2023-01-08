/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:02:45 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/08 04:46:02 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// see https://www.alanzucconi.com/2016/02/03/2d-rotations/

void	rotate_player(t_player *player, int angle)
{
	double	cos_phi_x;
	double	cos_phi_y;
	double	pos_x;
	double	pos_y;
	double	teta;

	teta = ((double)angle * PI) / 180;
	pos_x = player->pos.x;
	pos_y = player->pos.y;
	player->pos.x = pos_x * cos(teta) - pos_y * sin(teta);
	player->pos.y = pos_x * sin(teta) + pos_y * cos(teta);
}

void	rotate_img(t_img *img, double angle)
{
	
}