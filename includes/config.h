/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:43 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:51:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

// --=======----=======-- WINDOWS --=======----=======--
# define SCREEN_WIDTH 1024 // 1024 1920 2560 3840
# define SCREEN_HEIGHT 720 // 720 1080 720 1440 2160
# define SIZE_CHUNK 64

// --=======----=======-- UI --=======----=======--
# define UI_RATIO 3.5

// --=======----=======-- FPS --=======----=======--
# define FPS_VSYNC 0.00828 //0.00828

// --=======----=======-- CAMERA --=======----=======--
# define CAM_SPEED 500

// --=======----=======-- GRAPHISM --=======----=======--
# define HAS_CAM_ANIM 1

// --=======----=======-- MAP --=======----=======--
# ifndef SEED
#  define SEED 0
# endif

// --=======----=======-- END --=======----=======--
# define END_TIME 2

// --=======----=======-- DEBUG --=======----=======--
# define ISDEBUG 0

#endif