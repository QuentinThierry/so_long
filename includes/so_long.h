/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/06 19:53:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mlx/mlx.h"

// --=======----=======-- SCREEN_SIZE --=======----=======--
# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 500

// --=======----=======-- KEY_MAP --=======----=======--
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 10000
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 10
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum layers
{
	e_background,
	e_fps,
	e_player
};

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	struct s_img	*img[3];
	int				fps;
	int				offset_x;
	int				offset_y;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// utils.c
t_point	point(int x, int y);
char	*ft_itoa(int n);


#endif