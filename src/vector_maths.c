/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:16:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/05 02:30:51 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

float	magnitude(t_vector2 vector)
{
	return (sqrtf((vector.x * vector.x) + (vector.y * vector.y)));
}

t_fvector2	normalize(t_vector2 vector)
{
	float	magn;

	magn = magnitude(vector);
	return ((t_fvector2){vector.x / magn, vector.y / magn});
}

float	distance(t_vector2 src, t_vector2 dest)
{
	return (sqrtf((dest.y - src.y) * (dest.y - src.y) 
		+ (dest.x - src.x) * (dest.x - src.x)));
}