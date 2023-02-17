/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:02:24 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 03:01:23 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clear_image(t_sprite *pict)
{
	int	y;

	y = 0;
	while (y < pict->size.y)
	{
		ft_bzero(pict->img_ptr->data + y * pict->size.x * pict->opp,
			pict->size.x * pict->opp);
		y++;
	}
}
