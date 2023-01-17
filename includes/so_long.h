/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/17 17:10:43 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/extensions/Xrender.h>
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

// --=======----=======-- WINDOWS --=======----=======--
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 720
# define SIZE_CHUNK 64

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

# define ALPHA_MASK 0xFF000000
# define RED 0xFFFF0000
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define WHITE 0xFFFFFFFF

// --=======----=======-- KEY_MAP --=======----=======--
# define PLAYER_SIZE_X 100
# define PLAYER_SIZE_Y 100

// --=======----=======-- MATHS --=======----=======--
# define PI 3.141592654

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 5
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 10

// --=======----=======-- PLAYER --=======----=======--
# define SPEED 250

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum e_layers
{
	e_lbackground,
	e_lfps,
	e_lplayer,
	e_ltile,
	e_ldebug
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

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_fvector2
{
	float	x;
	float	y;
}	t_fvector2;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	double			elapsed;
	struct s_canvas	*canvas;
	struct s_pict	*layers[5];
	struct s_player	*player;
	int				fps;
	int				offset_x;
	int				offset_y;
	void			(*press_on_key[NB_KEYS])(struct s_game *, int);
}	t_game;

typedef struct s_pict
{
	void				*img;
	char				*addr;
	struct s_vector2	size;
	struct s_vector2	origin;
	int					line_length;
	int					oct_per_pixel;
	int					endian;
}	t_pict;

typedef struct s_canvas
{
	struct s_pict		*pict;
	struct s_chunk		*chunks;
	bool				*chunks_to_redraw;
	struct s_vector2	nb_chunks;
	struct s_vector2	size;
	int					nl_offset;
}	t_canvas;

typedef struct s_chunk
{
	char		*addr;
	int			size_x;
	int			size_y;
	t_vector2	pos;
}	t_chunk;

typedef struct s_player
{
	t_vector2	*pos;
	t_fvector2	exact_pos;
	t_vector2	dir;
}	t_player;

typedef union u_color
{
	unsigned int color;
	struct
	{
		unsigned char blue;
		unsigned char green;
		unsigned char red;
		unsigned char alpha;
	};
}	u_color;


// utils.c
char			*ft_itoa(int n);
int				min(int value1, int value2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *dest, size_t n);
char			*get_address_at(t_pict *pict, int x, int y);


// keys.c
void			exec_on_w(t_game *mlx);

// rotation.c
void			rotate_player(t_player *player, int angle);
void			rotate_image(t_pict *pict, double angle);

// bettermlx.c;
unsigned int	get_color_at(t_pict *pict, t_vector2 pos);
void			blend_images(t_pict *back, t_pict *front, t_vector2 pos);
void			bettermlx_get_data_addr(t_pict *pict);

// player_move.c
void	move_player(t_game *game);
void	press_on_w(t_game *game, int is_release);
void	press_on_a(t_game *game, int is_release);
void	press_on_s(t_game *game, int is_release);
void	press_on_d(t_game *game, int is_release);
void	press_on_e(t_game *game, int is_release);

// image_flip.c
void	flip_image_y(t_pict *pict);
void	flip_image_x(t_pict *pict);

// debug.c
void	debug_calculate(t_game *game, t_pict *debug_image);

// main.c
void	draw_rectangle(t_pict *pict, t_vector2 pos, t_vector2 size, int color);


#endif