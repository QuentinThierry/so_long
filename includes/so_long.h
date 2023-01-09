/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/09 20:08:02 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <time.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/extensions/Xrender.h>
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

// --=======----=======-- SCREEN_SIZE --=======----=======--
# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 500

// --=======----=======-- KEY_MAP --=======----=======--
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_ESC 65307
# define NB_KEYS 7

// --=======----=======-- COLORS --=======----=======--

# define ALPHA_MASk 0xFF000000
# define RED 0xFF0000
# define GREEN 0xFF00
# define BLUE 0xFF

// --=======----=======-- KEY_MAP --=======----=======--
# define PLAYER_SIZE_X 100
# define PLAYER_SIZE_Y 100

// --=======----=======-- MATHS --=======----=======--
# define PI 3.141592654

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 100
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 10
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum e_layers
{
	e_background,
	e_fps,
	e_player,
	e_tile
};

enum e_key_map
{
	e_W,
	e_A,
	e_S,
	e_D,
	e_E,
	e_ESC
};

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	struct s_pict	*canvas;
	struct s_pict	*layers[4];
	struct s_player	*player;
	void			(*exec_on_key[NB_KEYS])(struct s_mlx *);
	int				fps;
	int				offset_x;
	int				offset_y;
}	t_mlx;

typedef struct s_pict
{
	void	*img;
	char	*addr;
	int		line_length;
	int		oct_per_pixel;
	int		endian;
	int		width;
	int		height;
}	t_pict;

//typedef struct 

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_dvector2
{
	int	x;
	int	y;
}	t_dvector2;

typedef struct s_player
{
	t_vector2	pos;
	t_dvector2	rot;
}	t_player;

// utils.c
char			*ft_itoa(int n);
int				min(int value1, int value2);
void	*ft_memmove(void *dest, const void *src, size_t n);

// keys.c
void			exec_on_w(t_mlx *mlx);

// rotation.c
void			rotate_player(t_player *player, int angle);

// bettermlx.c;
unsigned int	get_color_at(t_pict *img, t_vector2 pos);
void			blend_images(t_pict *back, t_pict *front);
unsigned int	get_blended_color(unsigned int color_depth_back,
					unsigned int color_depth_front, t_vector2 pos);
void			bettermlx_get_data_addr(t_pict *pict);

#endif