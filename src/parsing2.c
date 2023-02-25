/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:47:47 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 17:58:45 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

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

char	**read_map(int fd, int *x, int *y)
{
	char	**map;
	t_list	*list;
	t_list	*tmp;
	char	*line;

	list = NULL;
	line = no_nl_gnl(fd);
	if (!line)
		return (no_nl_gnl(-1), close(fd), NULL);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			free_list(&list);
			return (no_nl_gnl(-1), close(fd), NULL);
		}
		ft_lstadd_back(&list, tmp);
		line = no_nl_gnl(fd);
	}
	map = list_to_map(list, x, y);
	free_list(&list);
	close(fd);
	return (map);
}
