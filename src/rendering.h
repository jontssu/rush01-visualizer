/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:12:49 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/21 14:33:46 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "window.h"
# include "mesh.h"
# include "ft_math.h"

typedef struct s_pixel
{
	t_int2		position;
	float		depth;
	t_float3	color;
}	t_pixel;

int		draw_mesh(t_frame *buf, t_mesh *mesh, t_float4x4 *matrix);
void	draw_line(t_frame *i, t_pixel a, t_pixel b);

#endif
