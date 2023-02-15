/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:16:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/15 20:36:36 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_vector2	add_vector2(t_vector2 vec1, t_vector2 vec2)
{
	vec1.x += vec2.x; 
	vec1.y += vec2.y;
	return (vec1);
}

t_vector2	sub_vector2(t_vector2 vec1, t_vector2 vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	return (vec1);
}

void	cpy_vector(t_vector2 *dest, t_vector2 src)
{
	dest->x = src.x;
	dest->y = src.y;
}

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

int	sqrdistance(t_vector2 src, t_vector2 dest)
{
	return (abs(dest.y - src.y) + abs(dest.x - src.x));
}

t_fvector2	direction_normalized(t_vector2 src, t_vector2 dest)
{
	t_fvector2	dir;

	dir = (t_fvector2){dest.x - src.x, dest.y - src.y};
	dir = normalize((t_vector2){dir.x, dir.y});
	return (dir);
}
