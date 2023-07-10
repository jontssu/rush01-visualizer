/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:17:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/10 13:27:24 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

#include "window.h"
#include "ft_math.h"

#include <mlx.h>

static t_pixel	vert_to_pixel(t_vertex vertex, t_float4x4 *mat, t_frame *buf)
{
	const t_int2	mid = {buf->width / 2, buf->height / 2};
	t_pixel			new;

	vertex.position = float3_transform(mat, vertex.position);
	new.position.x = (mid.x + (mid.x * vertex.position.x)) + 0.5;
	new.position.y = (mid.y - (mid.y * vertex.position.y)) + 0.5;
	new.depth = vertex.position.z;
	new.color = vertex.color;
	return (new);
}

static t_dynarr	get_pixels(t_dynarr *vert, t_float4x4 *mat, t_frame *buf)
{
	const t_vertex	*it = vert->ptr;
	const t_vertex	*end = it + vert->size;
	t_dynarr		pixel_buffer;
	t_pixel			pixel;

	pixel_buffer = (t_dynarr){};
	if (!dynarr_init(&pixel_buffer, vert->size, sizeof(t_pixel)))
		return (pixel_buffer);
	while (it != end)
	{
		pixel = vert_to_pixel(*it, mat, buf);
		if (!dynarr_pushback(&pixel_buffer, &pixel, 1))
			break ;
		it++;
	}
	return (pixel_buffer);
}

static void	draw_col(t_frame *buf, t_pixel *start, int points, int offset)
{
	while (--points)
	{
		draw_line(buf, *start, *(start + offset));
		start += offset;
	}
}

static void	draw_row(t_frame *buf, t_pixel *start, int points)
{
	while (--points)
	{
		draw_line(buf, *start, *(start + 1));
		start++;
	}
}

int	draw_mesh(t_frame *buf, t_mesh *mesh, t_float4x4 *matrix)
{
	t_dynarr	transformed_vertices;
	t_pixel		*pixel;
	t_int2		i;

	frame_clear(buf, 0x002E3440);
	transformed_vertices = get_pixels(&mesh->vertex_buffer, matrix, buf);
	pixel = transformed_vertices.ptr;
	if (!pixel)
		return (0);
	i = (t_int2){0, 0};
	while (i.x < mesh->width)
	{
		draw_col(buf, pixel + i.x, mesh->depth, mesh->width);
		i.x++;
	}
	while (i.y < mesh->depth)
	{
		draw_row(buf, pixel + (i.y * mesh->width), mesh->width);
		i.y++;
	}
	dynarr_del(&transformed_vertices);
	return (1);
}
