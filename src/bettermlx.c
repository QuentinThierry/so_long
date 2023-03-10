/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/24 02:53:01 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	btmlx_get_addr(t_sprite *sprite, t_img *img)
{
	sprite->img_ptr = img;
	sprite->opp = img->bpp / 8;
	sprite->line_length = img->size_line;
	sprite->endian = img->image->byte_order;
	sprite->size.x = img->width;
	sprite->size.y = img->height;
}

t_img	*resize_img(void *mlx, t_img *src,
					t_vector2 dst_size, t_vector2 src_size)
{
	t_img		*dst;
	t_fvector2	ratio;
	int			x;
	int			y;

	dst = mlx_new_image(mlx, dst_size.x, dst_size.y);
	if (!dst)
		return (NULL);
	ratio.x = (double)(src_size.x) / (double)(dst_size.x);
	ratio.y = (double)(src_size.y) / (double)(dst_size.y);
	y = -1;
	while (++y < dst_size.y)
	{
		x = -1;
		while (++x < dst_size.x)
		{
			*(unsigned int *)(dst->data + (int)(y) *dst->size_line
					+ (int)(x) *(dst->bpp / 8))
				= *(unsigned int *)(src->data + (int)(y * ratio.y)
					*src->size_line
					+ (int)(x * ratio.x) *(src->bpp / 8));
		}
	}
	return (dst);
}

t_img	*btmlx_xpm_file_to_image(void *mlx, char *path,
			t_vector2 dst_size)
{
	t_img		*src;
	t_img		*dst;
	t_vector2	src_size;

	if (!dst_size.x || !dst_size.y)
		return (NULL);
	src = mlx_xpm_file_to_image(mlx, path, &src_size.x, &src_size.y);
	if (!src)
		return (NULL);
	if ((src_size.x == dst_size.x && src_size.y == dst_size.y)
		|| (dst_size.x == 0 || dst_size.y == 0))
		return (src);
	dst = resize_img(mlx, src, dst_size, src_size);
	if (!dst)
		return (mlx_destroy_image(mlx, src), NULL);
	mlx_destroy_image(mlx, src);
	return (dst);
}
