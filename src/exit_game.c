/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:06:41 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 16:50:16 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>

static void	_free_images(t_game *game, t_img **img)
{
	int	i;

	i = 0;
	if (!img)
		return ;
	while (i < e_nb_img)
	{
		if (img[i])
			mlx_destroy_image(game->mlx, img[i]);
		i++;
	}
	free(img);
}

static void	_free_player(t_player *player)
{
	if (!player)
		return ;
	free(player->sprite);
	free(player->collider);
	free(player);
}

static void	_free_enemies(t_enemy **enemies)
{
	int	i;

	if (!enemies)
		return ;
	i = 0;
	while (enemies[i])
	{
		free(enemies[i]->collider);
		free(enemies[i]->sprite);
		free(enemies[i]);
		i++;
	}
	free(enemies);
}

static void	_free_level(t_game *game, t_level *lvl)
{
	if (!lvl)
		return ;
	_free_images(game, lvl->images);
	if (lvl->cam)
		free(lvl->cam->sprite);
	free(lvl->cam);
	free(lvl->background);
	_free_player(lvl->player1);
	_free_player(lvl->player2);
	_free_enemies(lvl->enemies);
	(free(lvl->wall_col), free(lvl->collec_col),
		free(lvl->enemy_col), free(lvl->exit_col), free(lvl->map));
	free(lvl->path_grid);
	free(lvl->debug_sprite);
	free(lvl->debug_tile_sprite);
	free(lvl->arrow);
	free(lvl->end_screen);
	free(lvl->ui);
	free(lvl->dist_table);
	if (!lvl->canvas)
		return ;
	free(lvl->canvas->chunks);
	free(lvl->canvas->chunks_to_redraw);
	free(lvl->canvas->sprite);
	free(lvl->canvas);
}

void	exit_game(t_game *game, const char *error)
{
	if (error)
		write(1, error, ft_strlen(error));
	if (!game)
		return ;
	_free_level(game, game->lvl);
	free(game->lvl);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (!game->tot_frame)
		game->tot_frame = 1;
	if (error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
//write(1, "DEBUG : \n\tFPS average : ", 24);
//ft_putnbr_fd((float)game->tot_fps/game->tot_frame, 1);
