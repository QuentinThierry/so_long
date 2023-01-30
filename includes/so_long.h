/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/30 20:03:25 by qthierry         ###   ########.fr       */
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
# include <fcntl.h>
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

// --=======----=======-- WINDOWS --=======----=======--
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
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
# define BLACK 0xFF000000

// --=======----=======-- KEY_MAP --=======----=======--
# define PLAYER_SIZE_X 100
# define PLAYER_SIZE_Y 100

// --=======----=======-- FPS --=======----=======--
// # define FPS_VSYNC 0.00828
# define FPS_VSYNC 0.00828
# define FRAME_RATE_DRAW_SPEED 1
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 10
# define FPS_COLOR BLACK

// --=======----=======-- PLAYER --=======----=======--
# define SPEED 250

// --=======----=======-- DEBUG --=======----=======--
# define ISDEBUG 0

// --=======----=======-- TEXTURES --=======----=======--
# define NB_VARIANT 5

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum e_images
{
	e_fps,
	e_player,
	e_ground,
	e_wall,
	e_collec,
	e_ennemy,
	e_exit,
	e_background
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

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

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
	int				fps;
	struct s_level	*lvl;
	void			(*press_on_key[NB_KEYS])(struct s_game *, int);
}	t_game;

typedef struct s_level
{
	struct s_canvas		*canvas;
	char				*map;
	struct s_sprite		*camera;
	struct s_vector2	map_size;
	struct s_player		*player;
	struct s_sprite		*sprites[16];
	struct s_collider	*stat_collision;
	struct s_collider	*dyn_collision;

}	t_level;

typedef struct s_canvas
{
	struct s_sprite		*sprite;
	struct s_chunk		*chunks;
	int					*chunks_to_redraw;
	struct s_vector2	nb_chunks;
	struct s_vector2	size;
	struct s_vector2	origin;
	struct s_fvector2	exact_origin;
	int					nl_offset;
}	t_canvas;

typedef struct s_collider
{
	int					id;
	struct s_vector2	min;
	struct s_vector2	size;
	struct s_vector2	max;
}	t_collider;

typedef struct s_sprite
{
	struct s_pict		*var[NB_VARIANT];
	int					current_var;
	struct s_vector2	size;
	struct s_vector2	pos;
	int					line_length;
	int					opp;
	int					endian;
}	t_sprite;

typedef struct s_pict
{
	void				*img;
	char				*addr;
}	t_pict;

typedef struct s_chunk
{
	char		*addr;
	int			variant;
	t_vector2	size;
	t_vector2	pos;
}	t_chunk;

typedef struct s_player
{
	t_collider	*collider;
	t_vector2	*pos;
	t_vector2	dir;
}	t_player;

typedef union u_color
{
	unsigned int	color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	};
}	t_color;

// others
void	my_mlx_pixel_put(t_sprite *sprite, int x, int y, unsigned int color);

// utils.c
char			*ft_itoa(int n);
int				min(int value1, int value2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *dest, size_t n);
char			*get_address_at(t_sprite *sprite, int x, int y);
size_t			ft_strlen(const char *s);
int				equals(char	*s1, char *s2);
void			pre_init_variants(t_sprite *sprite);

// list.c
t_list			*ft_lstnew(char *content);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *elem);
void			free_list(t_list **lst);

// load_images.c
void			load_images_default(t_game *game);
void			load_images_forest(t_game *game);

// parsing.c
int				parse_map(const char *file_name, char **map,
					t_vector2 *map_size);
void			free_tab2d(char ***to_free, int size_y);

// keys.c
void			exec_on_w(t_game *mlx);

// camera.c
void			render_camera(t_level *lvl, t_vector2 pos);

// bettermlx.c
void			btmlx_get_data_addr(t_sprite *sprite);
t_img			*btmlx_xpm_file_to_image(void *mlx, char *path,
					t_vector2 dst_size);

// chunks.c
int				init_chunks(t_level *lvl);
void			draw_to_chunk(t_canvas *canvas, int chunk, t_sprite *src);
void			draw_to_chunk(t_canvas *canvas, int chunk, t_sprite *src);
void			recalculate_chunks(t_level *lvl);
void			find_chunk_under(t_canvas *canvas, t_sprite *sprite);

// chunk_utils.c
t_sprite		*image_at_chunk(t_level *lvl, int chunk);
char			letter_at_chunk(t_level *lvl, int chunk);
int				pos_to_chunk(t_level *lvl, int x, int y);
void			clear_chunks_to_redraw(t_canvas *canvas);

// init_collision.c
int				init_collisions(t_level *lvl);

// collision.c
t_collider		*check_player_collision(t_level *lvl);

// player_move.c
void			move_player(t_game *game, int is_x, int is_y);
void			reverse_move_player(t_game *game, int is_x, int is_y);
void			press_on_w(t_game *game, int is_release);
void			press_on_a(t_game *game, int is_release);
void			press_on_s(t_game *game, int is_release);
void			press_on_d(t_game *game, int is_release);
void			press_on_e(t_game *game, int is_release);

// animations.c
void			calculate_animations(t_game *game);

// image_flip.c
void			flip_image_y(t_sprite *sprite);
void			flip_image_x(t_sprite *sprite);

// image_operations.c
int				draw_image_on_canvas(t_canvas *canvas, t_sprite *sprite,
					t_vector2 pos, int is_alpha_sensitive);
void			clear_image(t_sprite *sprite);

// colors.c
unsigned int	get_color_at(t_sprite *sprite, t_vector2 pos);
void			blend_images(t_sprite *back, t_sprite *front, t_vector2 pos);

// debug.c
void			debug_calculate(t_level *lvl);

// main.c
void			draw_rectangle(t_sprite *sprite, t_vector2 pos,
					t_vector2 size, int color);

#endif