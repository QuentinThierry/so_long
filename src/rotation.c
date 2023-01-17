/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:02:45 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/17 01:10:15 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// see https://www.alanzucconi.com/2016/02/03/2d-rotations/

void	rotate_player(t_player *player, int angle)
{
	double	pos_x;
	double	pos_y;
	double	teta;

	teta = ((double)angle * PI) / 180;
	pos_x = player->pos->x;
	pos_y = player->pos->y;
	player->pos->x = pos_x * cos(teta) - pos_y * sin(teta);
	player->pos->y = pos_x * sin(teta) + pos_y * cos(teta);
}

//void rotate_image(t_pict *pict, double angle)
//{
//    int x, y;
//    int size_x = pict->size.x;
//    int size_y = pict->size.y;
//    double center_x = size_x / 2.0;
//    double center_y = size_y / 2.0;
//    unsigned int *original_img = (unsigned int*)(pict->addr);

//    angle = angle * PI / 180; // convert degree to radians

//    for (y = 0; y < size_y; y++)
//    {
//        for (x = 0; x < size_x; x++)
//        {
//            double dx = x - center_x;
//            double dy = y - center_y;
//            double rx = dx * cos(angle) - dy * sin(angle);
//            double ry = dx * sin(angle) + dy * cos(angle);
//            int new_x = rx;
//            int new_y = ry;
//            if (new_x >= 0 && new_x < size_x && new_y >= 0 && new_y < size_y)
//            {
//                unsigned int *original_px = original_img + y * size_x + x;
//                unsigned int *new_px = original_img + new_y * size_x + new_x;
//                unsigned int tmp = *original_px;
//                *original_px = *new_px;
//                *new_px = tmp;
//            }
//        }
//    }
//}