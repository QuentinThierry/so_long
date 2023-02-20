/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:19:42 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/20 19:25:42 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

int	find_exit_chunk(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == 'E')
			return (i);
		++i;
	}
	return (-1);
}

static int	is_ber(const char *file_name)
{
	size_t	size;

	size = ft_strlen(file_name);
	if (size <= 3)
		return (0);
	if (equals((char *)(file_name + (size - 4)), ".ber"))
		return (1);
	return (0);
}

void	free_tab2d(char **to_free, int size_y)
{
	int	i;

	i = 0;
	while (i < size_y)
	{
		free((to_free)[i]);
		i++;
	}
	free(to_free);
}

static char	*get_line_as_tab(char *line)
{
	int		i;
	int		size;
	char	*res;

	size = ft_strlen(line);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static int	is_rectangle(t_list *list, int size)
{
	while (list)
	{
		if (size != (int)ft_strlen(list->content))
			return (0);
		list = list->next;
	}
	return (1);
}

static char	**list_to_map(t_list *list, int *x, int *y)
{
	char	**map;
	int		i;

	*y = ft_lstsize(list);
	if (*y < 3)
		return (NULL);
	*x = ft_strlen(list->content);
	if (*x < 3)
		return (NULL);
	if (!is_rectangle(list, *x))
		return (NULL);
	map = malloc(sizeof(char *) * *y);
	if (!map)
		return (NULL);
	i = -1;
	while (++i < *y)
	{
		map[i] = get_line_as_tab(list->content);
		if (!map[i])
			return (free_tab2d(map, i), NULL);
		list = list->next;
	}
	return (map);
}

static char	*no_nl_gnl(int fd)
{
	char	*line;
	size_t	size;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	size = ft_strlen(line);
	if (size <= 0)
		return (NULL);
	if (line[size - 1] == '\n')
		line[size - 1] = 0;
	return (line);
}

static char	**read_map(int fd, int *x, int *y)
{
	char	**map;
	t_list	*list;
	t_list	*tmp;
	char	*line;

	list = NULL;
	line = no_nl_gnl(fd);
	if (!line)
		return (no_nl_gnl(-1), NULL);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			free_list(&list);
			return (no_nl_gnl(-1), NULL);
		}
		ft_lstadd_back(&list, tmp);
		line = no_nl_gnl(fd);
	}
	map = list_to_map(list, x, y);
	free_list(&list);
	return (map);
}

int	is_closed(char **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		if (map[0][i] != '1' || map[y - 1][i] != '1')
			return (0);
		while ((i == 0 || i == x - 1) && j < y - 1)
		{
			if (map[j][i] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	change_flag(char letter, int flag)
{
	if (letter == 'E')
	{
		if ((flag & 0x1) != 0)
			return (-1);
		flag |= 0x1;
	}
	if (letter == 'P')
	{
		if ((flag & 0x2) != 0)
			return (-1);
		flag |= 0x2;
	}
	if (letter == 'C')
		flag |= 0x4;
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

char	*map2d_to_1d(char **map2D, t_vector2 map_size)
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

	x = 0;
	if (!is_ber(file_name))
		return (0);
	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), 0);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	map2d = read_map(fd, &x, &y);
	close(fd);
	if (!map2d)
		return (0);
	if (!is_closed(map2d, x, y))
		return (free_tab2d(map2d, y), 0);
	if (!has_all_elem_once(map2d, x, y))
		return (free_tab2d(map2d, y), 0);
	*map_size = (t_vector2){x, y};
	*map = map2d_to_1d(map2d, *map_size);
	free_tab2d(map2d, y);
	if (!*map)
		return (0);
	return (1);
}
