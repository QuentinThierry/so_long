/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:44:26 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 19:56:37 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


int	print_key(int key)
{
	printf("coucou %d\n", key);
	return (0);
}


int main(int argc, char const *argv[])
{
	void	*mlx;
	void	*mlx_window;
	int		i;
	int		j;

	i = 100;
	j = 100;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "Trop cool");
	
	while (j < 10000)
	{
		usleep(15000);
		while (i < 200)
		{
			mlx_pixel_put(mlx, mlx_window, i + j, 50, 0xffffff00 + j);
			i++;
		}
		j++;
		printf("test\n");
	}

	printf("test\n");
	// mlx_put_image_to_window(mlx, mlx_window, NULL, 0, 0);

	mlx_key_hook(mlx_window, print_key, NULL);
	mlx_loop(mlx);

	(void)argc;
	(void)argv;
	return 0;
}
