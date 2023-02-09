NAME = so_long
CFLAGS = -g3 -Wall -Wextra -Ofast #-Werror
DEPS = $(INCLUDES)so_long.h $(INCLUDES)get_next_line.h  $(INCLUDES)textures.h Makefile
INCLUDES = includes/
SRC_DIR = src/
OBJ_DIR = obj/
CC = clang
LIBS = -L$(INCLUDES)mlx -lmlx -lXext -lX11 -lm

SRC = $(addprefix $(SRC_DIR), \
	animations.c \
	bettermlx.c \
	camera.c \
	chunks_utils.c \
	chunks.c \
	collision.c \
	colors.c \
	debug.c \
	draw_game.c \
	init_enemies.c \
	enemies_movement.c \
	get_next_line_utils.c \
	get_next_line.c \
	image_flip.c \
	image_operations.c \
	init_collision.c \
	init_lvl_base.c \
	keys.c \
	list_utils.c \
	load_forest_images.c\
	parsing.c \
	pathfinding.c \
	player_move.c \
	sprite_choose.c \
	utils.c \
	vector_maths.c \
	main.c)

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DEPS) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

bonus : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus