/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:11 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 20:44:31 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <sys/types.h>
# include <time.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "textures.h"
# include "config.h"

// --=======----=======-- KEY_MAP --=======----=======--
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_L 108
# define KEY_LA 65361
# define KEY_UA 65362
# define KEY_RA 65363
# define KEY_DA 65364
# define KEY_8 65431
# define KEY_4 65430
# define KEY_5 65437
# define KEY_6 65432
# define KEY_ENTER 65307
# define KEY_ESC 65293
# define NB_KEYS 16

// --=======----=======-- COLORS --=======----=======--
# define ALPHA_MASK 0xFF000000
# define RED 0xFFFF0000
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define WHITE 0xFFFFFFFF
# define BLACK 0xFF000000

// --=======----=======-- FPS --=======----=======--
# define FRAME_RATE_DRAW_SPEED 100
# define FPS_POSX 10
# define FPS_POSY 20
# define FPS_WIDTH 35
# define FPS_HEIGHT 10
# define FPS_COLOR BLACK


// --=======----=======-- PLAYER --=======----=======--
# define SPEED 250
# define PLAYER_WIDTH 42
# define PLAYER_HEIGHT 34

// --=======----=======-- ENEMIES --=======----=======--
# define ENEMY_SPEED 175
# define DISTANCE_AGGRO 300

// --=======----=======-- ANIMATIONS --=======----=======--
# define CAM_ANIM_TIME_SEC 5
# define OFFSET_CAM_LOAD SIZE_CHUNK
# define ANIM_NB_IDLE_P 6
# define ANIM_RARE_IDLE_CHANCE_P 3
# define ANIM_TIME_IDLE0_P 0.3
# define ANIM_TIME_IDLE1_P 1
# define ANIM_TIME_RUN_P 0.2
# define ANIM_NB_RUN_P 8
# define ANIM_NB_IDLE0_E 5
# define ANIM_NB_IDLE1_E 14
# define ANIM_RARE_IDLE_CHANCE_E 10
# define ANIM_TIME_IDLE0_E 0.3
# define ANIM_TIME_IDLE1_E 0.3
# define ANIM_TIME_RUN_E 0.1
# define ANIM_NB_RUN_E 5

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum e_key_map
{
	e_W,
	e_A,
	e_S,
	e_D,
	e_P,
	e_L,
	e_LA,
	e_UA,
	e_RA,
	e_DA,
	e_8,
	e_4,
	e_5,
	e_6,
	e_ENTER,
	e_ESC
};

enum e_col_type
{
	e_col_wall,
	e_col_collec,
	e_col_ennemy
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
	long			tot_fps;
	long			tot_frame;
	struct s_level	*lvl;
	int				is_end;
	void			(*press_on_key[NB_KEYS])(struct s_game *, int);
}	t_game;

typedef struct s_level
{
	struct s_canvas		*canvas;
	struct s_img		**images;
	struct s_camera		*cam;
	struct s_sprite		*background;
	struct s_player		*player1;
	struct s_player		*player2;
	struct s_enemy		**enemies;
	struct s_collider	*wall_col;
	struct s_collider	*collec_col;
	struct s_collider	*enemy_col;
	struct s_collider	*exit_col;
	char				*map;
	struct s_vector2	map_size;
	struct s_path_case	*path_grid;
	struct timeval		start_time;
	int					nb_collec;
	int					max_collec;
	int					is_animating_cam;
	int					exit_chunk;
	int					nb_move;
	struct s_sprite		*debug_sprite;
	struct s_sprite		*debug_tile_sprite;
	int					*dist_table;
}	t_level;

typedef struct s_canvas
{
	struct s_sprite		*sprite;
	struct s_chunk		*chunks;
	int					*chunks_to_redraw;
	struct s_vector2	nb_chunks;
	struct s_vector2	size;
	struct s_vector2	origin;
	struct s_vector2	pos_exit;
	int					nl_offset;
}	t_canvas;

typedef struct s_camera
{
	struct s_sprite		*sprite;
	struct s_vector2	*pos;
	t_fvector2			exact_pos;
	t_fvector2			dir;
	struct s_vector2	*size;
	int					has_been_triggered;
	int					is_cam_lock;
}	t_camera;

typedef struct s_collider
{
	int					id;
	int					*image_id;
	struct s_vector2	*pos;
	struct s_vector2	*size;
	int					has_been_triggered;
}	t_collider;

typedef struct s_path_case
{
	int	tot;
	int	dst_start;
	int	has_been_check;
	int	parent;
}	t_path_case;

typedef struct s_enemy
{
	int					id;
	struct s_sprite		*sprite;
	t_vector2			*size;
	t_vector2			*pos;
	struct timeval		anim_time;
	t_fvector2			exact_pos;
	t_fvector2			dir;
	struct s_collider	*collider;
	int					is_triggered;
	struct s_player		*target;
}	t_enemy;

typedef struct s_sprite
{
	int					image_id;
	t_img				*img_ptr;
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
	int			image_id;
	t_vector2	size;
	t_vector2	pos;
}	t_chunk;

typedef struct s_player
{
	t_sprite	*sprite;
	t_collider	*collider;
	t_vector2	*pos;
	t_fvector2	exact_pos;
	t_vector2	dir;
	int			is_look_left;
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
void			my_mlx_pixel_put(t_sprite *sprite,
					int x, int y, unsigned int color);

// draw_game.c
int				draw_on_window(t_game *game);

// utils.c
char			*ft_itoa(int n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *dest, size_t n);
char			*get_address_at(t_sprite *sprite, int x, int y);
size_t			ft_strlen(const char *s);
int				equals(char	*s1, char *s2);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_sec_ft_memcpy(void *dest, const void *src,
					size_t n, t_sprite *sprite);

// list.c
t_list			*ft_lstnew(char *content);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *elem);
void			free_list(t_list **lst);

// load_images_forest.c
void			load_images_forest(t_game *game);
void			init_base_images(t_game *game);

// parsing.c
int				parse_map(const char *file_name, char **map,
					t_vector2 *map_size);
void			free_tab2d(char **to_free, int size_y);
int				find_exit_chunk(char *map);

// camera.c
void			render_camera(t_level *lvl, t_vector2 pos);
void			move_camera(t_game *game);

// camera_utils.c
t_vector2		get_offset_for_cam(t_camera *cam, t_vector2 pos_to_offset);
int				is_inside_load_range(t_game *game, t_vector2 pos);
int				is_inside_camera(t_camera *cam, t_vector2 pos);

// bettermlx.c
void			btmlx_get_addr(t_sprite *sprite, t_img *img);
t_img			*btmlx_xpm_file_to_image(void *mlx, char *path,
					t_vector2 dst_size);

// init_lvl_base.c
void			init_lvl_base(t_game *game);
void			init_player2(t_game *game);

// sprite_choose.c
enum e_img_id	choose_image(char *map, int chunk);

// chunks.c
int				init_chunks(t_level *lvl);
void			recalculate_chunks(t_level *lvl);
void			find_chunk_under(t_canvas *canvas, t_sprite *sprite);

// chunk_utils.c
t_img			*image_at_chunk(t_level *lvl, int chunk);
char			letter_at_chunk(t_level *lvl, int chunk);
int				pos_to_chunk(t_level *lvl, int x, int y);
void			clear_chunks_to_redraw(t_canvas *canvas);

// init_collision.c
int				init_collisions(t_level *lvl);

// collision.c
t_collider		*check_wall_collision(t_level *lvl, t_collider *src);
void			check_col_collectible(t_game *game);
void			check_col_enemy(t_game *game);
void			check_col_exit(t_game *game);

// player_move.c
void			player_movement(t_game *game, t_player *player);

// init_enemies.c
int				init_enemies(t_game *game);	

//enemies_movement.c
void			enemy_movement(t_game *game);
void			check_trigger_enemy(t_game *game, t_player *player);

// keys.c
enum e_key_map	get_key(int key);
int				press_key(int key, t_game *game);
int				release_key(int key, t_game *game);
void			press_on_w(t_game *game, int is_release); // up p1
void			press_on_a(t_game *game, int is_release); // left p1
void			press_on_s(t_game *game, int is_release); // down p1
void			press_on_d(t_game *game, int is_release); // right p1
void			press_on_p(t_game *game, int is_release); // skip cam anim
void			press_on_l(t_game *game, int is_release); // lock/delock cam
void			press_on_ua(t_game *game, int is_release); // up move cam
void			press_on_la(t_game *game, int is_release); // left move cam
void			press_on_da(t_game *game, int is_release); // down move cam
void			press_on_ra(t_game *game, int is_release); // rigth move cam
void			press_on_enter(t_game *game, int status); // join new player
void			press_on_8(t_game *game, int is_release); // up p2
void			press_on_4(t_game *game, int is_release); // left p2
void			press_on_5(t_game *game, int is_release); // down p2
void			press_on_6(t_game *game, int is_release); // right p2
void			press_on_esc(t_game *game, int is_release); // quit

// exit_game.c
void			exit_game(t_game *game);

// end_game.c
void			end_game(t_game *game);

// vector_maths.c
float			magnitude(t_vector2 vector);
t_fvector2		normalize(t_vector2 vector);
float			distance(t_vector2 src, t_vector2 dest);
int				sqrdistance(t_vector2 src, t_vector2 dest);
t_fvector2		direction_normalized(t_vector2 src, t_vector2 dest);

t_vector2		add_vector2(t_vector2 vec1, t_vector2 vec2); 
t_vector2		sub_vector2(t_vector2 vec1, t_vector2 vec2);
void			cpy_vector(t_vector2 *dest, t_vector2 src);

//pathfinding.c
int				a_star(t_game *game, t_vector2 src, char **path_map);

// check_valid_path.c
int				check_valid_path(t_game *game);

// animations.c
void			camera_animation_to_exit(t_level *lvl);
void			play_animations(t_game *game);

// animations_enemies.c
void			play_anim_enemy(t_game *game, t_enemy *enemy);

// animations_player
void			play_anim_player1(t_game *game);
void			play_anim_player2(t_game *game);

// image_flip.c
void			flip_image_y(t_sprite *sprite);
void			flip_image_x(t_sprite *sprite);

// image_operations.c
void			clear_image(t_sprite *sprite);

// colors.c
unsigned int	get_color_at(t_sprite *sprite, t_vector2 pos);
void			blend_image_to_image(t_sprite *back,
					t_sprite *front, t_vector2 pos);

// draw_line.c
void			draw_line(t_camera *camra,
					t_vector2 src, t_vector2 dest, t_color color);

// debug.c
void			debug_calculate(t_level *lvl);
void			draw_shortest_path(t_level *lvl, int end);

// main.c
void			draw_rectangle(t_sprite *sprite, t_vector2 pos,
					t_vector2 size, int color);
int				on_update(t_game *game);

#endif