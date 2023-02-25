/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:19:42 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 17:54:26 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

static int	change_flag(char letter, int flag)
{
	if (letter == 'E')
	{
		if ((flag & 0x1) != 0)
			return (-1);
		flag |= 0x1;
	}
	else if (letter == 'P')
	{
		if ((flag & 0x2) != 0)
			return (-1);
		flag |= 0x2;
	}
	else if (letter == 'C')
		flag |= 0x4;
	else if (letter != 'S' && letter != '1' && letter != '0')
		return (-1);
	return (flag);
}

static int	has_all_elem_once(char **map, int x, int y)
{
	int		flag;
	int		i;
	int		j;

	j = 0;
	flag = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			flag = change_flag(map[j][i], flag);
			if (flag == -1)
				return (0);
			i++;
		}
		j++;
	}
	if ((flag & 0x07) != 0x07)
		return (0);
	return (1);
}

static char	*map2d_to_1d(char **map2D, t_vector2 map_size)
{
	char	*map;
	int		x;
	int		y;

	map = malloc(sizeof(char) * map_size.x * map_size.y + (sizeof(char) * 1));
	if (!map)
		return (NULL);
	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			map[y * map_size.x + x] = map2D[y][x];
			x++;
		}
		y++;
	}
	map[map_size.y * map_size.x] = 0;
	return (map);
}

int	parse_map(const char *file_name, char **map, t_vector2 *map_size)
{
	char	**map2d;
	int		fd;
	int		x;
	int		y;

	if (!is_ber(file_name))
		return (0);
	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), 0);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	map2d = read_map(fd, &x, &y);
	if (!map2d)
		return (0);
	if (!is_closed(map2d, x, y))
		return (free_tab2d(map2d, y), 0);
	if (!has_all_elem_once(map2d, x, y))
		return (free_tab2d(map2d, y), 0);
	*map_size = (t_vector2){x, y};
	*map = map2d_to_1d(map2d, *map_size);
	if (!*map)
		return (free_tab2d(map2d, y), 0);
	return (free_tab2d(map2d, y), 1);
}
