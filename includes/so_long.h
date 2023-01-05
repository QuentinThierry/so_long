/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/05 02:20:19 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mlx/mlx.h"

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 1000
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 15
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		fps;
}	t_mlx;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// utils.c
t_point	point(int x, int y);
char	*ft_itoa(int n);


#endif