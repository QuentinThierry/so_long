NAME = so_long
CFLAGS = -g3 -Wall -Wextra -Ofast #-Werror
DEPS = $(INCLUDES)so_long.h $(INCLUDES)get_next_line.h Makefile
INCLUDES = includes/
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
LIBS = -L$(INCLUDES)mlx -lmlx -lXext -lX11 -lm

SRC = $(addprefix $(SRC_DIR), \
	get_next_line.c \
	get_next_line_utils.c \
	utils.c \
	load_images.c \
	bettermlx.c \
	player_move.c \
	chunks_utils.c \
	init_collision.c \
	animations.c \
	collision.c \
	camera.c \
	image_flip.c \
	image_operations.c \
	colors.c \
	chunks.c \
	parsing.c \
	list_utils.c \
	debug.c \
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