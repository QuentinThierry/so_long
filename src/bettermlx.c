/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bettermlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by qthierry          #+#    #+#             */
/*   Updated: 2023/02/06 19:14:26 by qthierry         ###   ########.fr       */
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

static t_img	*resize_img(void *mlx, t_img *src,
					t_vector2 dst_size, t_vector2 src_size)
{
	t_img		*dst;
	t_fvector2	ratio;
	int	x;
	int	y;

	dst = mlx_new_image(mlx, dst_size.x, dst_size.y);
	if (!dst)
		return (NULL);
	ratio.x = (double)(dst_size.x) / (double)(src_size.x);
	ratio.y = (double)(dst_size.y) / (double)(src_size.y);
	y = 0;
	while (y < src_size.y)
	{
		x = 0;
		while (x < src_size.x)
		{
			*(unsigned int *)(dst->data + (int)(y * ratio.y) * dst->size_line
				+ (int)(x * ratio.x) * (dst->bpp / 8)) =
				*(unsigned int *)(src->data + y * src->size_line
				+ x * (src->bpp / 8));
			x++;
		}
		y++;
	}
	free(src);
	return (dst);
}

// do not use at run time, big malloc
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
	dst = resize_img(mlx, src, dst_size, src_size);
	if (!dst)
		return((free(src), NULL));
	return (dst);
}
