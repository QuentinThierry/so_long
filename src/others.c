/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:45:02 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:45:15 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_sprite *sprite, t_vector2 pos, unsigned int color)
{
	char	*dst;

	dst = sprite->img_ptr->data
		+ (pos.y * sprite->line_length + pos.x * sprite->opp);
	*(unsigned int *)(dst) = color;
}

void	calculate_fps(int *fps, double *elapsed)
{
	static struct timeval	prev_time = {0, 0};
	struct timeval			tmp;
	double					delay;

	if (!prev_time.tv_sec)
		gettimeofday(&prev_time, NULL);
	gettimeofday(&tmp, NULL);
	delay = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC)
			+ tmp.tv_sec - prev_time.tv_sec);
	while (delay < FPS_VSYNC)
	{
		gettimeofday(&tmp, NULL);
		delay = (((double)(tmp.tv_usec - prev_time.tv_usec) / CLOCKS_PER_SEC)
				+ tmp.tv_sec - prev_time.tv_sec);
	}
	*elapsed = delay + (!delay);
	*fps = (int)(1.0 / *elapsed);
	prev_time = tmp;
}

void	move_camera_on_player(t_camera *cam, t_player *player)
{
	*cam->pos = (t_vector2){
		player->pos->x - SCREEN_WIDTH / 2 + player->sprite->size.x / 2,
		player->pos->y - SCREEN_HEIGHT / 2 + player->sprite->size.y / 2};
	cam->exact_pos = (t_fvector2){cam->pos->x, cam->pos->y};
}

void	update_cam_pos(t_game *game)
{
	if (game->lvl->cam->is_cam_lock == 1)
		move_camera_on_player(game->lvl->cam, game->lvl->player1);
	else
		move_camera(game);
}

void	draw_arrow_to_end(t_level *lvl, t_player *player)
{
	t_vector2	pos_arrow;
	t_vector2	player_pos_mid;
	t_vector2	exit_pos;
	t_fvector2	norm_dir;

	exit_pos = lvl->canvas->chunks[lvl->exit_chunk].pos;
	player_pos_mid = add_vector2(*player->pos,
			(t_vector2){player->sprite->size.x / 2,
			player->sprite->size.y / 2});
	norm_dir = direction_normalized(player_pos_mid, exit_pos);
	pos_arrow = (t_vector2){norm_dir.x * DIST_ARROW, norm_dir.y * DIST_ARROW};
	pos_arrow = get_offset_for_cam(lvl->cam,
			add_vector2(pos_arrow, player_pos_mid));
	if (!is_inside_camera(lvl->cam, pos_arrow))
		return ;
	blend_image_to_image(lvl->cam->sprite, lvl->arrow, pos_arrow);
}
