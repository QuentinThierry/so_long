/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:54:41 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 17:56:38 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

int	is_ber(const char *file_name)
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
