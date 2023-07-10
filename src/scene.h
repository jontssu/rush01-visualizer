/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:14:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/20 09:17:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "input.h"
# include "mesh.h"
# include "ft_math.h"
# include "rendering.h"

typedef struct s_scene
{
	t_cam		camera;
	t_transform	camera_transform;
	t_mesh		mesh;
	t_transform	mesh_transform;
	t_float4x4	scene_matrix;
}	t_scene;

int		scene_init(t_scene *empty, const char *mesh_path);
void	scene_del(t_scene *scene);

void	scene_update(t_scene *scene, t_input *input);

#endif
