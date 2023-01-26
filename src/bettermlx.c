/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/26 18:28:49 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	bettermlx_get_data_addr(t_pict *pict)
{
	t_img	*img;

	img = pict->img;
	pict->addr = img->data;
	pict->opp = img->bpp / 8;
	pict->line_length = img->size_line;
	pict->endian = img->image->byte_order;
	pict->size.x = img->width;
	pict->size.y = img->height;
	pict->pos.x = 0;
	pict->pos.y = 0;
}