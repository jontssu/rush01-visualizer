/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:47:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/10 19:08:32 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	get_height_values(t_mesh *mesh, float *min, float *max)
{
	const t_vertex	*it = mesh->vertex_buffer.ptr;
	const t_vertex	*end = it + mesh->vertex_buffer.size;

	*min = 0;
	*max = 0;
	while (it != end)
	{
		if (it->position.y < *min)
			*min = it->position.y;
		else if (it->position.y > *max)
			*max = it->position.y;
		it++;
	}
}

void	calculate_mesh_colors(t_mesh *mesh)
{
	const t_float3	mid_color = {0.30, 0.34, 0.42};
	float			max;
	float			min;
	t_vertex		*it;
	t_vertex		*end;

	get_height_values(mesh, &min, &max);
	it = mesh->vertex_buffer.ptr;
	end = it + mesh->vertex_buffer.size;
	while (it != end)
	{
		switch ((int)it->position.y)
		{
			case 1: it->color = (t_float3){0.96, 0.43, 0.60}; break;
			case 2: it->color = (t_float3){0.58, 0.38, 0.89}; break;
			case 3: it->color = (t_float3){0.40, 0.45, 0.80}; break;
			case 4: it->color = (t_float3){0.20, 0.56, 0.86}; break;
			case 5: it->color = (t_float3){0.30, 0.75, 0.71}; break;
			case 6: it->color = (t_float3){0.22, 0.76, 0.44}; break;
			case 7: it->color = (t_float3){1.00, 0.93, 0.29}; break;
			case 8: it->color = (t_float3){0.96, 0.60, 0.25}; break;
			case 9: it->color = (t_float3){0.89, 0.20, 0.18}; break;
			default: it->color = mid_color; break;
		}
		it++;
	}
}

void	center_mesh(t_mesh *mesh)
{
	const float	offset_x = (float)(mesh->width - 1) / 2;
	const float	offset_z = (float)(mesh->depth - 1) / 2;
	t_vertex	*it;
	t_vertex	*end;

	it = mesh->vertex_buffer.ptr;
	end = it + mesh->vertex_buffer.size;
	while (it != end)
	{
		it->position.x -= offset_x;
		it->position.z -= offset_z;
		it++;
	}
}
