/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:44:51 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/20 09:38:07 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "window.h"
# include "input.h"
# include "scene.h"

typedef struct s_app
{
	t_window	window;
	t_input		input;
	t_scene		scene;
}	t_app;

int	app_init(t_app *instance, char *map_path);
int	app_terminate(t_app *instance, int exit_code);

int	app_mlx_loop(t_app *app);

#endif
