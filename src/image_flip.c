/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_flip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:06:33 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/16 20:14:12 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flip_image_y(t_pict *pict)
{
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	unsigned	tmp;

	x = 0;
	y = 0;
	size_x = pict->size.x;
	size_y = pict->size.y;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x / 2)
		{
			tmp = *(unsigned int*)(pict->addr + x * 4 + (y) * pict->line_length);
			*(unsigned int*)(pict->addr + (x * 4) + (y) * pict->line_length)
			
			=	*(unsigned int*)(pict->addr + (size_x - x) * 4 + (y) * pict->line_length);
				*(unsigned int*)(pict->addr + (size_x - x) * 4 + (y) * pict->line_length) = tmp;
			
			x++;
		}
		y++;
	}
}

// void	flip_image_x(t_pict *pict)
// {
// 	int			x;
// 	int			y;
// 	int			size_x;
// 	int			size_y;
// 	unsigned	tmp;

// 	x = 0;
// 	y = 0;
// 	size_x = pict->size.x;
// 	size_y = pict->size.y;
// 	while (y < size_y)
// 	{
// 		x = 0;
// 		while (x < size_x / 2)
// 		{
// 			tmp = *(unsigned int*)(pict->addr + x * 4 + (y) * pict->line_length);
// 			*(unsigned int*)(pict->addr + (x * 4) + (y) * pict->line_length)
			
// 			=	*(unsigned int*)(pict->addr + (size_x - x) * 4 + (y) * pict->line_length);
// 				*(unsigned int*)(pict->addr + (size_x - x) * 4 + (y) * pict->line_length) = tmp;
			
// 			x++;
// 		}
// 		y++;
// 	}
// }