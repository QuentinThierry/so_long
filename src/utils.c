/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:05:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/11 20:06:32 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static size_t	get_size(unsigned int n)
{
	size_t	size;

	if (!n)
		return (1);
	size = 0;
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	ncpy;
	char			*res;
	size_t			size;

	size = (n < 0);
	ncpy = n * (1 | -size);
	size += get_size(ncpy);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size--] = '\0';
	if (!ncpy)
		res[0] = '0';
	while (ncpy > 0)
	{
		res[size] = (ncpy % 10) + '0';
		ncpy /= 10;
		size--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

int	min(int value1, int value2)
{
	if (value1 < value2)
		return (value1);
	return (value2);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while ((n - i) % sizeof(size_t))
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		i++;
	}
	while (i < n)
	{
		*(size_t *)(dest + i) = *(size_t *)(src + i);
		i += sizeof(size_t);
	}
	return (dest);
}

// use in chunk_to_draw
void	ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	while ((n - i) % sizeof(size_t))
	{
		*(unsigned char *)dest = 0;
		i++;
	}
	while (i < n)
	{
		*(size_t *)(dest + i) = 0;
		i += sizeof(size_t);
	}
}
