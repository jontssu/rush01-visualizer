/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:02:06 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 12:13:23 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

#include <math.h>

float	lerp(float start, float end, float factor)
{
	return ((1 - factor) * start + factor * end);
}

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	rad(float deg)
{
	return (deg * (M_PI / 180));
}
