/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:21 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/11 01:44:54 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

// --=======----=======-- IDS --=======----=======--

enum e_img_id
{
	e_canvas,
	e_camera,
	e_movement,
	e_background,
	e_debug,
	e_debug_tile,
	e_player_0,
	e_player_1,
	e_player_2,
	e_player_3,
	e_player_4,
	e_player_5,
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
	e_enemy_0_0,
	e_enemy_0_1,
	e_enemy_0_2,
	e_enemy_0_3,
	e_enemy_0_4,
	e_enemy_1_0,
	e_enemy_1_1,
	e_enemy_1_2,
	e_enemy_1_3,
	e_enemy_1_4,
	e_enemy_2_0,
	e_enemy_2_1,
	e_enemy_2_2,
	e_enemy_2_3,
	e_enemy_2_4,
	e_enemy_3_0,
	e_enemy_3_1,
	e_enemy_3_2,
	e_enemy_3_3,
	e_enemy_3_4,
	e_nb_img
};

// --=======----=======-- IMAGES --=======----=======--

# define FOREST_BACKGROUND "assets/forest/forest_background.xpm"

# define FOREST_SQR_IDLE "assets/squirrel/squirrel_idle0_0.xpm"
# define FOREST_EXIT "assets/forest/forest_exit.xpm"

// GROUND 0
# define FOREST_GROUND "assets/forest/forest_ground.xpm"
# define FOREST_GRASS "assets/forest/forest_grass.xpm"
# define FOREST_STONE "assets/forest/forest_stone.xpm"
# define FOREST_STICK "assets/forest/forest_stick.xpm"

// COLLECTIBLES C
# define FOREST_FLOWER_R "assets/forest/forest_flower_red.xpm"
# define FOREST_FLOWER_Y "assets/forest/forest_flower_yellow.xpm"
# define FOREST_FLOWER_D "assets/forest/forest_flower_d.xpm"

// ENNEMIES G
# define FOREST_GHOST "assets/forest/forest_ghost.xpm"
# define FOREST_GHOST_A "assets/forest/forest_ghost_angry.xpm"

# define FOREST_TREE1 "assets/forest/forest_tree.xpm"
# define FOREST_TREE2 "assets/forest/forest_tree2.xpm"

// DEBUG
# define DEBUG_TILE "assets/others/debug_tile.xpm"

#endif