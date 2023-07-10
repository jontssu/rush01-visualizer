/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/20 09:21:34 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "ft_math.h"

# include <mlx.h>

typedef struct s_input
{
	char	exit;
	char	move;
	char	rotate;
	char	zoom;
	char	projection_mode;
	float	mouse_sens;
	t_int2	mouse_position;
	t_int2	mouse_movement;
}	t_input;

void	input_init(t_input *empty, void *mlx_window);

#endif
