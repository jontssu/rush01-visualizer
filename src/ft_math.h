/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:59:59 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 12:13:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

typedef struct s_int2
{
	int	x;
	int	y;
}	t_int2;

typedef struct s_int3
{
	int	x;
	int	y;
	int	z;
}	t_int3;

typedef struct s_float3
{
	float	x;
	float	y;
	float	z;
}	t_float3;

typedef struct s_float4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_float4;

typedef struct s_float4x4
{
	t_float4	a;
	t_float4	b;
	t_float4	c;
	t_float4	d;
}	t_float4x4;

typedef struct s_transform
{
	t_float3	position;
	t_float3	rotation;
	t_float3	scale;
}	t_transform;

float		lerp(float start, float end, float factor);
float		clamp(float value, float min, float max);
float		rad(float deg);

t_int2		int2_add(t_int2 l, t_int2 r);
t_int2		int2_sub(t_int2 l, t_int2 r);

t_int3		int3_add(t_int3 l, t_int3 r);
t_int3		int3_sub(t_int3 l, t_int3 r);

t_float3	float3_add(t_float3 l, t_float3 r);
t_float3	float3_sub(t_float3 l, t_float3 r);
t_float3	float3_scalar(t_float3 l, float multiplier);
t_float3	float3_lerp(t_float3 start, t_float3 end, float factor);
t_float3	float3_cross(t_float3 l, t_float3 r);
t_float3	float3_normalize(t_float3 vec);
t_float3	float3_transform(const t_float4x4 *l, t_float3 r);
t_float3	float3_rot_x(t_float3 l, float rad);
t_float3	float3_rot_y(t_float3 l, float rad);
t_float3	float3_rot_z(t_float3 l, float rad);

float		float3_len(t_float3 vector);

t_float4x4	float4x4_mul(const t_float4x4 *l, const t_float4x4 *r);
t_float4x4	float4x4_ortho(float size, float aspect, float near, float far);
t_float4x4	float4x4_persp(float fov, float aspect, float near, float far);
t_float4x4	float4x4_view(t_float3 pos, t_float3 x, t_float3 y, t_float3 z);
t_float4x4	float4x4_model(const t_transform *transform);
t_float4x4	float4x4_translation(t_float3 pos);
t_float4x4	float4x4_rotation(t_float3 rot);
t_float4x4	float4x4_scaling(t_float3 scale);

#endif
