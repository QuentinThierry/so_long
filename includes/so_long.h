/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/09 01:37:55 by qthierry         ###   ########.fr       */
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

// --=======----=======-- KEY_MAP --=======----=======--
# define PLAYER_SIZE_X 100
# define PLAYER_SIZE_Y 100

// --=======----=======-- MATHS --=======----=======--
#define PI 3.141592654

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 10
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
	struct s_pict	*imgs[4];
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
	int		bits_per_pixel;
	int		endian;
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
t_vector2	vector(int x, int y);
char	*ft_itoa(int n);

// keys.c
void	exec_on_w(t_mlx *mlx);

// rotation.c
void rotate_player(t_player *player, int angle);

// bettermlx.c;
unsigned int	get_color_at(t_pict *img, t_vector2 pos);
void			apply_transparency_on_image(t_mlx *mlx);
unsigned int	get_blended_color(t_mlx *mlx, t_vector2 pos);

#endif