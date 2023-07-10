/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:26:30 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 10:49:00 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

#include <math.h>

t_float3	float3_transform(const t_float4x4 *l, t_float3 r)
{
	t_float3	out;
	float		out_w;

	out.x = l->a.x * r.x + l->a.y * r.y + l->a.z * r.z + l->a.w;
	out.y = l->b.x * r.x + l->b.y * r.y + l->b.z * r.z + l->b.w;
	out.z = l->c.x * r.x + l->c.y * r.y + l->c.z * r.z + l->c.w;
	out_w = l->d.x * r.x + l->d.y * r.y + l->d.z * r.z + l->d.w;
	if (out_w != 1.0)
	{
		out.x /= out_w;
		out.y /= out_w;
		out.z /= out_w;
	}
	return (out);
}

t_float3	float3_normalize(t_float3 vector)
{
	const float	len = float3_len(vector);

	vector.x /= len;
	vector.y /= len;
	vector.z /= len;
	return (vector);
}

t_float3	float3_rot_x(t_float3 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float3	result;

	result.x = l.x;
	result.y = (l.y * dcos) - (l.z * dsin);
	result.z = (l.y * dsin) + (l.z * dcos);
	return (result);
}

t_float3	float3_rot_y(t_float3 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float3	result;

	result.x = (l.x * dcos) + (l.z * dsin);
	result.y = l.y;
	result.z = -(l.x * dsin) + (l.z * dcos);
	return (result);
}

t_float3	float3_cross(t_float3 l, t_float3 r)
{
	return ((t_float3){
		l.y * r.z - l.z * r.y,
		l.z * r.x - l.x * r.z,
		l.x * r.y - l.y * r.x
	});
}
