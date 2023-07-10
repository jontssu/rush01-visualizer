/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:31:54 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 12:12:18 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

#include "input.h"

void	cam_init(t_cam *empty, float fov, int is_ortho)
{
	empty->is_ortho = is_ortho;
	empty->ortho_scale = 1.0;
	empty->ortho_size = 100;
	empty->fov = fov;
	empty->aspect = 1.0;
	empty->near = 0.1;
	empty->far = 100;
	empty->target = (t_float3){};
	empty->x = (t_float3){1.0, 0.0, 0.0};
	empty->y = (t_float3){0.0, 1.0, 0.0};
	empty->z = (t_float3){0.0, 0.0, 1.0};
}

void	cam_update(t_cam *camera, t_transform *transform, t_input *input)
{
	const float	mouse_x = input->mouse_movement.x * input->mouse_sens;
	const float	mouse_y = input->mouse_movement.y * input->mouse_sens;

	camera->is_ortho = !input->projection_mode;
	if (input->rotate)
	{
		transform->position = float3_rot_y(transform->position, mouse_x);
	}
	if (input->zoom)
	{
		camera->ortho_scale += mouse_y;
		camera->ortho_scale = clamp(camera->ortho_scale, 0.1, 3.0);
		camera->fov += mouse_y;
		camera->fov = clamp(camera->fov, rad(1), rad(110));
	}
	camera->z = float3_sub(transform->position, camera->target);
	camera->z = float3_normalize(camera->z);
	camera->y = (t_float3){0.0, 1.0, 0.0};
	camera->x = float3_cross(camera->y, camera->z);
	camera->x = float3_normalize(camera->x);
	camera->y = float3_cross(camera->z, camera->x);
}

t_float4x4	cam_calc_projection(const t_cam *view)
{
	float	size;

	if (view->is_ortho)
	{
		size = view->ortho_scale * view->ortho_size;
		return (float4x4_ortho(size, view->aspect, view->near, view->far));
	}
	else
	{
		return (float4x4_persp(view->fov, view->aspect, view->near, view->far));
	}
}

t_float4x4	cam_calc_view(const t_cam *camera, const t_transform *transform)
{
	return (float4x4_view(transform->position,
			camera->x, camera->y, camera->z));
}
