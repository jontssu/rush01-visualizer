/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:16:58 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 11:45:18 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

#include <math.h>

#define ISO_ANGLE 35.264

static	t_float4x4	calc_scene_matrix(t_scene *source)
{
	t_float4x4	view;
	t_float4x4	proj;
	t_float4x4	model;
	t_float4x4	scene_matrix;

	view = cam_calc_view(&source->camera, &source->camera_transform);
	proj = cam_calc_projection(&source->camera);
	model = float4x4_model(&source->mesh_transform);
	scene_matrix = float4x4_mul(&proj, &view);
	scene_matrix = float4x4_mul(&scene_matrix, &model);
	return (scene_matrix);
}

int	scene_init(t_scene *empty, const char *mesh_path)
{
	t_transform	*t;

	if (!mesh_import(&empty->mesh, mesh_path))
	{
		return (0);
	}
	cam_init(&empty->camera, rad(90), 0);
	t = &empty->camera_transform;
	t->position = (t_float3){0.0, 0.0, 1.0};
	t->position = float3_rot_x(t->position, rad(-ISO_ANGLE));
	t->position = float3_rot_y(t->position, rad(45));
	t->position = float3_scalar(t->position, empty->mesh.width * 1.2);
	empty->camera.far = float3_len(t->position) * 4;
	empty->camera.near = empty->camera.far * 0.5;
	empty->camera.ortho_size = empty->mesh.width / 2;
	t = &empty->mesh_transform;
	t->position = (t_float3){0.0, 0.0, 0.0};
	t->rotation = (t_float3){0.0, 0.0, 0.0};
	t->scale = (t_float3){1.0, 1.0, 1.0};
	empty->scene_matrix = calc_scene_matrix(empty);
	return (1);
}

void	scene_del(t_scene *scene)
{
	mesh_del(&scene->mesh);
}

void	scene_update(t_scene *scene, t_input *input)
{
	const float		mouse_x = input->mouse_movement.x * input->mouse_sens;
	const float		mouse_y = input->mouse_movement.y * input->mouse_sens;
	t_float3 *const	pos = &scene->mesh_transform.position;

	cam_update(&scene->camera, &scene->camera_transform, input);
	if (input->move)
	{
		*pos = float3_add(*pos, float3_scalar(scene->camera.x, -mouse_x * 4));
		*pos = float3_add(*pos, float3_scalar(scene->camera.y, mouse_y * 4));
	}
	scene->scene_matrix = calc_scene_matrix(scene);
}
