/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:43 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/17 02:08:55 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
// --=======----=======-- WINDOWS --=======----=======--
# define SCREEN_WIDTH 1024 // 1920 1024 2560 3840
# define SCREEN_HEIGHT 720 // 1080 720 1440 2160
# define SIZE_CHUNK 64

// --=======----=======-- FPS --=======----=======--
// # define FPS_VSYNC 0.00828
# define FPS_VSYNC 0.000000828

// --=======----=======-- CAMERA --=======----=======--
# define CAM_SPEED 500

// --=======----=======-- GRAPHISM --=======----=======--
# define HIGH_GRPHISM 1
# define HAS_CAM_ANIM 0

// --=======----=======-- MAP --=======----=======--
# ifndef SEED
#  define SEED 0
# endif

// --=======----=======-- DEBUG --=======----=======--
# define ISDEBUG 0

#endif