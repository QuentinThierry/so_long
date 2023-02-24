/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:53:25 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/24 01:55:09 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	_play_on_win_game(t_game *game, double elapsed)
{
	int		i;
	t_color	color;
	char	*dst;

	i = 0;
	while (i < game->lvl->cam->size->y * game->lvl->cam->size->x)
	{
		color.alpha = (0xFF * elapsed * (1 / (float)END_TIME));
		color.red = 0;
		color.green = 0;
		color.blue = 0;
		dst = game->lvl->end_screen->img_ptr->data + i
			* game->lvl->cam->sprite->opp;
		*(unsigned int *)dst = color.color;
		i++;
	}
	blend_image_to_image(game->lvl->cam->sprite,
		game->lvl->end_screen, (t_vector2){0, 0});
}

double	get_elapsed(struct timeval *prev_time)
{
	struct timeval	tmp;
	double			elapsed;

	gettimeofday(&tmp, NULL);
	elapsed = (((double)(tmp.tv_usec - prev_time->tv_usec) / CLOCKS_PER_SEC)
			+ tmp.tv_sec - prev_time->tv_sec);
	return (elapsed);
}

void	end_game(t_game *game)
{
	static struct timeval	time = {0, 0};
	double					elapsed;

	if (!time.tv_sec)
		gettimeofday(&time, NULL);
	elapsed = get_elapsed(&time);
	_play_on_win_game(game, elapsed);
	if ((elapsed) > END_TIME)
		exit_game(game);
}
