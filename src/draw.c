/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:14:29 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 10:49:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	put_pixel(t_frame *buf, t_int2 pos, float z, t_float3 color)
{
	char			*pixel;
	float			*depth;
	unsigned int	mlx_color;

	if (pos.x < 0 || pos.y < 0 || pos.x >= buf->width || pos.y >= buf->height)
		return ;
	depth = buf->depth_buffer + (pos.x + pos.y * buf->width);
	if (*depth < z)
		return ;
	pixel = buf->data + ((pos.x + pos.y * buf->width) * buf->color_bytes);
	mlx_color = (unsigned char)(255 * color.x) << 16;
	mlx_color = (unsigned char)(255 * color.y) << 8 | mlx_color;
	mlx_color = (unsigned char)(255 * color.z) | mlx_color;
	*depth = z;
	*(unsigned int *)pixel = mlx_color;
}

static int	ft_abs(int i)
{
	return (i * ((i > 0) - (i < 0)));
}

static t_float3	calc_color_offset(t_int2 delta, t_float3 c0, t_float3 c1)
{
	t_float3	color_offset;

	if (delta.x >= -delta.y)
		color_offset = float3_scalar(float3_sub(c1, c0), 1.0f / delta.x);
	else
		color_offset = float3_scalar(float3_sub(c1, c0), 1.0f / -delta.y);
	return (color_offset);
}

static float	calc_depth_offset(t_int2 delta, float d0, float d1)
{
	float	depth_offset;

	if (delta.x >= -delta.y)
		depth_offset = (d1 - d0) * (1.0f / delta.x);
	else
		depth_offset = (d1 - d0) * (1.0f / -delta.y);
	return (depth_offset);
}

void	draw_line(t_frame *target, t_pixel a, t_pixel b)
{
	float		depth_offset;
	t_float3	color_offset;
	t_int2		delta;
	t_int2		dir;
	t_int2		err;

	delta.x = ft_abs(b.position.x - a.position.x);
	delta.y = -ft_abs(b.position.y - a.position.y);
	color_offset = calc_color_offset(delta, a.color, b.color);
	depth_offset = calc_depth_offset(delta, a.depth, b.depth);
	dir.x = -1 + (2 * (a.position.x < b.position.x));
	dir.y = -1 + (2 * (a.position.y < b.position.y));
	err.x = delta.x + delta.y;
	while (a.position.x != b.position.x || a.position.y != b.position.y)
	{
		put_pixel(target, a.position, a.depth, a.color);
		a.color = float3_add(a.color, color_offset);
		a.depth += depth_offset;
		err.y = 2 * err.x;
		err.x += delta.y * (err.y >= delta.y);
		a.position.x += dir.x * (err.y >= delta.y);
		err.x += delta.x * (err.y <= delta.x);
		a.position.y += dir.y * (err.y <= delta.x);
	}
	put_pixel(target, a.position, a.depth, a.color);
}
