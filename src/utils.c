/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:05:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 17:43:55 by qthierry         ###   ########.fr       */
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	size;

	size = sizeof(size_t);
	i = 0;
	if (n > size)
	{
		while (i < n - size)
		{
			*(size_t *)(dest + i) = *(size_t *)(src + i);
			i += size;
		}
	}
	while (i != n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

void	ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	if (n > sizeof(size_t))
	{
		while (i < n - sizeof(size_t))
		{
			*(size_t *)(dest + i) = 0;
			i += sizeof(size_t);
		}
	}
	while (i != n)
	{
		*(unsigned char *)(dest + i) = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	const char	*cpy;

	cpy = s;
	while (*s)
		s++;
	return ((size_t)(s - cpy));
}
