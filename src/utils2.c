/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:44:06 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/25 17:44:23 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = ((char *)s)[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static void	_ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ncpy;

	ncpy = n * (1 | -(n < 0));
	if (n < 0)
		write(fd, "-", 1);
	if (ncpy >= 10)
	{
		ft_putnbr_fd(ncpy / 10, fd);
		ft_putnbr_fd(ncpy % 10, fd);
	}
	else
		_ft_putchar_fd(ncpy + '0', fd);
}
