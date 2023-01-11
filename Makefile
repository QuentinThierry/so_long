NAME = so_long
CFLAGS = -g3 -Wall -Wextra #-Werror
DEPS = $(INCLUDES)so_long.h Makefile
INCLUDES = includes/
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
LIBS = -L$(INCLUDES)mlx -lmlx -lXext -lX11 -lm

SRC = $(addprefix $(SRC_DIR), \
	utils.c \
	rotation.c \
	bettermlx.c \
	player_move.c \
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