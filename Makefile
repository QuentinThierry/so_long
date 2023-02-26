NAME =		so_long
CFLAGS =	-Wall -Wextra -Werror#-O3 #-fsanitize=address #-g3
MLX_DIR =	$(INCLUDES)mlx/
MLX = 		$(MLX_DIR)libmlx.a
DEPS =		$(INCLUDES)so_long.h \
			$(INCLUDES)get_next_line.h \
			$(INCLUDES)textures.h \
			$(INCLUDES)config.h \
			Makefile
INCLUDES	= includes/
SRC_DIR		= src/
OBJ_DIR		= obj/
CC =		gcc
LIBS =		-L$(INCLUDES)mlx -lmlx -lXext -lX11 -lm

SRC =		$(addprefix $(SRC_DIR), \
			animations.c \
			animations_enemies.c \
			animations_player.c \
			bettermlx.c \
			camera.c \
			camera_utils.c \
			check_valid_path.c \
			chunks_utils.c \
			chunks.c \
			collision.c \
			collision_utils.c \
			colors.c \
			debug.c \
			draw_game.c \
			draw_line.c \
			exit_game.c \
			exit_on_cross.c \
			end_game.c \
			enemies_movement.c \
			enemies_movement_utils.c \
			get_next_line_utils.c \
			get_next_line.c \
			init_enemies.c \
			init_on_start.c \
			image_flip.c \
			image_operations.c \
			init_collision.c \
			init_lvl_base.c \
			init_lvl_base2.c \
			keys1.c \
			keys2.c \
			keys3.c \
			keys4.c \
			list_utils.c \
			load_forest_images.c \
			load_forest_images2.c \
			parsing.c \
			parsing2.c \
			parsing3.c \
			pathfinding.c \
			pathfinding2.c \
			player_move.c \
			others.c \
			sprite_choose.c \
			utils.c \
			utils2.c \
			vector_maths.c \
			main.c)

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(MLX) $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

bonus : $(NAME)

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(MLX_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus