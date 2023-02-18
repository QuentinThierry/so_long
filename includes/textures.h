/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:21 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/18 23:44:36 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

// --=======----=======-- IDS --=======----=======--

enum e_img_id
{
	e_canvas,
	e_camera,
	e_background,
	e_arrow,
	e_debug,
	e_debug_tile,
	e_player_idle_0_0,
	e_player_idle_0_1,
	e_player_idle_0_2,
	e_player_idle_0_3,
	e_player_idle_0_4,
	e_player_idle_0_5,
	e_player_idle_1_0,
	e_player_idle_1_1,
	e_player_idle_1_2,
	e_player_idle_1_3,
	e_player_idle_1_4,
	e_player_idle_1_5,
	e_player_run_0_0,
	e_player_run_0_1,
	e_player_run_0_2,
	e_player_run_0_3,
	e_player_run_0_4,
	e_player_run_0_5,
	e_player_run_0_6,
	e_player_run_0_7,
	e_ground0_0,
	e_ground0_1,
	e_ground0_2,
	e_ground0_3,
	e_ground0_4,
	e_ground1_0,
	e_ground1_1,
	e_ground1_2,
	e_ground1_3,
	e_ground1_4,
	e_ground2_0,
	e_ground2_1,
	e_ground2_2,
	e_ground2_3,
	e_ground2_4,
	e_ground3_0,
	e_ground3_1,
	e_ground3_2,
	e_ground3_3,
	e_ground3_4,
	e_wall0_0,
	e_wall0_1,
	e_wall0_2,
	e_wall0_3,
	e_wall0_4,
	e_wall1_0,
	e_wall1_1,
	e_wall1_2,
	e_wall1_3,
	e_wall1_4,
	e_wall2_0,
	e_wall2_1,
	e_wall2_2,
	e_wall2_3,
	e_wall2_4,
	e_wall3_0,
	e_wall3_1,
	e_wall3_2,
	e_wall3_3,
	e_wall3_4,
	e_exit_0,
	e_exit_1,
	e_exit_2,
	e_exit_3,
	e_exit_4,
	e_collec0_0,
	e_collec0_1,
	e_collec0_2,
	e_collec0_3,
	e_collec0_4,
	e_collec1_0,
	e_collec1_1,
	e_collec1_2,
	e_collec1_3,
	e_collec1_4,
	e_collec2_0,
	e_collec2_1,
	e_collec2_2,
	e_collec2_3,
	e_collec2_4,
	e_collec3_0,
	e_collec3_1,
	e_collec3_2,
	e_collec3_3,
	e_collec3_4,
	e_enemy_idle_0_0,
	e_enemy_idle_0_1,
	e_enemy_idle_0_2,
	e_enemy_idle_0_3,
	e_enemy_idle_0_4,
	e_enemy_idle_1_0,
	e_enemy_idle_1_1,
	e_enemy_idle_1_2,
	e_enemy_idle_1_3,
	e_enemy_idle_1_4,
	e_enemy_idle_1_5,
	e_enemy_idle_1_6,
	e_enemy_idle_1_7,
	e_enemy_idle_1_8,
	e_enemy_idle_1_9,
	e_enemy_idle_1_10,
	e_enemy_idle_1_11,
	e_enemy_idle_1_12,
	e_enemy_idle_1_13,
	e_enemy_run_0_0,
	e_enemy_run_0_1,
	e_enemy_run_0_2,
	e_enemy_run_0_3,
	e_enemy_run_0_4,
	e_nb_img
};

// --=======----=======-- IMAGES --=======----=======--

# define FOREST_BACKGROUND "assets/forest/forest_background.xpm"
# define ARROW "assets/others/arrow.xpm"

// PLAYER IDLE
# define FOREST_SQR_IDLE0_0 "assets/squirrel/squirrel_idle0_0.xpm"
# define FOREST_SQR_IDLE0_1 "assets/squirrel/squirrel_idle0_1.xpm"
# define FOREST_SQR_IDLE0_2 "assets/squirrel/squirrel_idle0_2.xpm"
# define FOREST_SQR_IDLE0_3 "assets/squirrel/squirrel_idle0_3.xpm"
# define FOREST_SQR_IDLE0_4 "assets/squirrel/squirrel_idle0_4.xpm"
# define FOREST_SQR_IDLE0_5 "assets/squirrel/squirrel_idle0_5.xpm"
# define FOREST_SQR_IDLE1_0 "assets/squirrel/squirrel_idle1_0.xpm"
# define FOREST_SQR_IDLE1_1 "assets/squirrel/squirrel_idle1_1.xpm"
# define FOREST_SQR_IDLE1_2 "assets/squirrel/squirrel_idle1_2.xpm"
# define FOREST_SQR_IDLE1_3 "assets/squirrel/squirrel_idle1_3.xpm"
# define FOREST_SQR_IDLE1_4 "assets/squirrel/squirrel_idle1_4.xpm"
# define FOREST_SQR_IDLE1_5 "assets/squirrel/squirrel_idle1_5.xpm"

// PLAYER RUN
# define FOREST_SQR_RUN0_0 "assets/squirrel/squirrel_run0_0.xpm"
# define FOREST_SQR_RUN0_1 "assets/squirrel/squirrel_run0_1.xpm"
# define FOREST_SQR_RUN0_2 "assets/squirrel/squirrel_run0_2.xpm"
# define FOREST_SQR_RUN0_3 "assets/squirrel/squirrel_run0_3.xpm"
# define FOREST_SQR_RUN0_4 "assets/squirrel/squirrel_run0_4.xpm"
# define FOREST_SQR_RUN0_5 "assets/squirrel/squirrel_run0_5.xpm"
# define FOREST_SQR_RUN0_6 "assets/squirrel/squirrel_run0_6.xpm"
# define FOREST_SQR_RUN0_7 "assets/squirrel/squirrel_run0_7.xpm"

// EXIT E
# define FOREST_EXIT "assets/forest/forest_exit.xpm"

// GROUND 0
# define FOREST_GROUND "assets/forest/forest_ground.xpm"
# define FOREST_GRASS "assets/forest/forest_grass.xpm"
# define FOREST_STONE "assets/forest/forest_stone.xpm"
# define FOREST_STICK "assets/forest/forest_stick.xpm"

// COLLECTIBLES C
# define FOREST_FLOWER_R "assets/forest/acorn.xpm"
# define FOREST_FLOWER_Y "assets/forest/acorn.xpm"
# define FOREST_FLOWER_D "assets/forest/acorn_empty.xpm"

// ENNEMIES G
# define SLIME_B_IDLE0_0 "assets/slime/slime_b_idle0_0.xpm"
# define SLIME_B_IDLE0_1 "assets/slime/slime_b_idle0_1.xpm"
# define SLIME_B_IDLE0_2 "assets/slime/slime_b_idle0_2.xpm"
# define SLIME_B_IDLE0_3 "assets/slime/slime_b_idle0_3.xpm"
# define SLIME_B_IDLE0_4 "assets/slime/slime_b_idle0_4.xpm"
# define SLIME_B_IDLE1_0 "assets/slime/slime_b_idle1_0.xpm"
# define SLIME_B_IDLE1_1 "assets/slime/slime_b_idle1_1.xpm"
# define SLIME_B_IDLE1_2 "assets/slime/slime_b_idle1_2.xpm"
# define SLIME_B_IDLE1_3 "assets/slime/slime_b_idle1_3.xpm"
# define SLIME_B_IDLE1_4 "assets/slime/slime_b_idle1_4.xpm"
# define SLIME_B_IDLE1_5 "assets/slime/slime_b_idle1_5.xpm"
# define SLIME_B_IDLE1_6 "assets/slime/slime_b_idle1_6.xpm"
# define SLIME_B_IDLE1_7 "assets/slime/slime_b_idle1_7.xpm"
# define SLIME_B_IDLE1_8 "assets/slime/slime_b_idle1_8.xpm"
# define SLIME_B_IDLE1_9 "assets/slime/slime_b_idle1_9.xpm"
# define SLIME_B_IDLE1_10 "assets/slime/slime_b_idle1_10.xpm"
# define SLIME_B_IDLE1_11 "assets/slime/slime_b_idle1_11.xpm"
# define SLIME_B_IDLE1_12 "assets/slime/slime_b_idle1_12.xpm"
# define SLIME_B_IDLE1_13 "assets/slime/slime_b_idle1_13.xpm"

# define SLIME_B_RUN0_0 "assets/slime/slime_b_run0_0.xpm"
# define SLIME_B_RUN0_1 "assets/slime/slime_b_run0_1.xpm"
# define SLIME_B_RUN0_2 "assets/slime/slime_b_run0_2.xpm"
# define SLIME_B_RUN0_3 "assets/slime/slime_b_run0_3.xpm"
# define SLIME_B_RUN0_4 "assets/slime/slime_b_run0_4.xpm"

# define FOREST_TREE1 "assets/forest/forest_tree.xpm"
# define FOREST_TREE2 "assets/forest/forest_tree2.xpm"

// DEBUG
# define DEBUG_TILE "assets/others/debug_tile.xpm"

#endif