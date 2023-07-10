/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/21 10:07:02 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

#ifdef __linux__
# include "linux/keycodes.h"
#else
# include "macos/keycodes.h"
#endif

#include <math.h> // M_PI

static int	keydown_hook(int keycode, t_input *input)
{
	if (keycode == KEY_ESCAPE)
		input->exit = 1;
	else if (keycode == KEY_P)
		input->projection_mode = !input->projection_mode;
	return (1);
}

static int	mousemove_hook(int x, int y, t_input *input)
{
	const t_int2	new_pos = {x, y};

	input->mouse_movement = int2_sub(input->mouse_position, new_pos);
	input->mouse_position = new_pos;
	return (1);
}

static int	mousedown_hook(int button, int x, int y, t_input *input)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		input->move = 1;
	else if (button == MOUSE_RIGHT)
		input->rotate = 1;
	else if (button == MOUSE_MID)
		input->zoom = 1;
	return (1);
}

static int	mouseup_hook(int button, int x, int y, t_input *input)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		input->move = 0;
	else if (button == MOUSE_RIGHT)
		input->rotate = 0;
	else if (button == MOUSE_MID)
		input->zoom = 0;
	return (1);
}

void	input_init(t_input *empty, void *mlx_window)
{
	empty->move = 0;
	empty->rotate = 0;
	empty->zoom = 0;
	empty->mouse_sens = 0.01;
	empty->projection_mode = 0;
	mlx_hook(mlx_window, ON_KEYDOWN, 0, keydown_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEDOWN, 0, mousedown_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEUP, 0, mouseup_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEMOVE, 0, mousemove_hook, empty);
}
