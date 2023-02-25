/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_on_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:37:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 18:42:07 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_keys(t_game *game)
{
	game->press_on_key[e_W] = &press_on_w;
	game->press_on_key[e_A] = &press_on_a;
	game->press_on_key[e_S] = &press_on_s;
	game->press_on_key[e_D] = &press_on_d;
	game->press_on_key[e_P] = &press_on_p;
	game->press_on_key[e_L] = &press_on_l;
	game->press_on_key[e_UA] = &press_on_ua;
	game->press_on_key[e_LA] = &press_on_la;
	game->press_on_key[e_DA] = &press_on_da;
	game->press_on_key[e_RA] = &press_on_ra;
	game->press_on_key[e_8] = &press_on_8;
	game->press_on_key[e_4] = &press_on_4;
	game->press_on_key[e_5] = &press_on_5;
	game->press_on_key[e_6] = &press_on_6;
	game->press_on_key[e_ENTER] = &press_on_esc;
	game->press_on_key[e_ESC] = &press_on_enter;
}

t_game	init_values(char *map, t_vector2 map_size)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init();
	game.lvl = ft_calloc(sizeof(t_level), 1);
	if (!game.lvl)
	{
		free(map);
		exit_game(&game, "Error\nAllocation error.\n");
	}
	game.lvl->map = map;
	game.lvl->map_size = map_size;
	game.lvl->exit_chunk = find_exit_chunk(game.lvl->map);
	load_images_forest(&game);
	init_lvl_base(&game);
	init_keys(&game);
	game.fps = 0;
	game.tot_fps = 0;
	game.elapsed = 0;
	game.tot_frame = 0;
	game.is_end = 0;
	return (game);
}

void	init_dist_table(t_level *lvl, int *table, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		table[i] = sqrdistance(lvl->canvas->chunks[i].pos,
				lvl->canvas->chunks[lvl->exit_chunk].pos) / SIZE_CHUNK;
		i++;
	}
}

void	init_ui(t_game *game)
{
	game->lvl->ui->pos.x = SCREEN_WIDTH / 2 - (game->lvl->ui->size.x / 2);
	game->lvl->ui->pos.y = 0;
}

void	init_map_variables(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->lvl->canvas->nb_chunks.y * game->lvl->canvas->nb_chunks.x)
	{
		game->lvl->canvas->chunks_to_redraw[i] = 1;
		if (game->lvl->map[i] == 'P')
		{
			*game->lvl->player1->pos = game->lvl->canvas->chunks[i].pos;
			game->lvl->player1->exact_pos.x = game->lvl->player1->pos->x;
			game->lvl->player1->exact_pos.y = game->lvl->player1->pos->y;
		}
		if (game->lvl->map[i] == 'C')
			game->lvl->max_collec++;
		i++;
	}
	recalculate_chunks(game->lvl);
	clear_chunks_to_redraw(game->lvl->canvas);
}
