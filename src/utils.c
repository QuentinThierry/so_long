/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:05:30 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/09 17:37:41 by qthierry         ###   ########.fr       */
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

inline int	min(int value1, int value2)
{
	if (value1 < value2)
		return (value1);
	return (value2);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > sizeof(size_t))
	{
		while (i < n - sizeof(size_t))
		{
			*(size_t *)(dest + i) = *(size_t *)(src + i);
			i += sizeof(size_t);
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

inline char	*get_address_at(t_sprite *sprite, int x, int y)
{
	return (sprite->img_ptr->data + (y * sprite->line_length) + (x * sprite->opp));
}

size_t	ft_strlen(const char *s)
{
	const char	*cpy;

	cpy = s;
	while (*s)
		s++;
	return ((size_t)(s - cpy));
}

int	equals(char	*s1, char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	if (!nmemb || !size)
		return (malloc(0));
	if ((size_t)-1 / nmemb < size)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (res);
	i = 0;
	while (i < (size * nmemb))
		((char *)res)[i++] = 0;
	return (res);
}
