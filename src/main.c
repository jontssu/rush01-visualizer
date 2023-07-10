/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:50:44 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 11:49:47 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

#include <mlx.h>

#include <libft.h>

int	main(int argc, char **argv)
{
	t_app	fdf;

	fdf = (t_app){};
	if (argc != 2)
	{
		ft_printf("Use: fdf <map_path>\n");
		return (1);
	}
	if (!app_init(&fdf, argv[1]))
	{
		app_terminate(&fdf, 1);
	}
	mlx_loop(fdf.window.mlx_handle);
	return (1);
}
