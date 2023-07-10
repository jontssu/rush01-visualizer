/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:48:33 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/10 13:40:45 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

#include <libft.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define MAP_READ_CHUNK_SIZE 64
#define MIN_VERTS 4

static int	read_map(t_dynarr *buffer, const char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);
	ssize_t		read_output;

	read_output = 1;
	if (fd < 0)
	{
		perror("Unable to open file");
		return (0);
	}
	while (read_output > 0)
		read_output = dynarr_read(buffer, fd, MAP_READ_CHUNK_SIZE);
	close(fd);
	if (read_output < 0)
	{
		dynarr_del(buffer);
		return (0);
	}
	dynarr_pushback(buffer, "\0", 1);
	return (1);
}

static int	parse_map(t_mesh *mesh, const t_dynarr *map_data)
{
	const char	*it = map_data->ptr;
	t_vertex	vertex;

	while (*it)
	{
		while (*it == ' ')
			it++;
		vertex.position = (t_float3){mesh->width++, ft_atoi(it), mesh->depth};
		if (!dynarr_pushback(&mesh->vertex_buffer, &vertex, 1))
			return (0);
		while (*it && *it != '\n' && *it != ' ')
			it++;
		while (*it == ' ')
			it++;
		if (*it == '\n')
		{
			mesh->width = 0;
			mesh->depth++;
			it++;
		}
	}
	mesh->width = mesh->vertex_buffer.size / mesh->depth;
	return (1);
}

int	mesh_import(t_mesh *empty, const char *filepath)
{
	t_dynarr	map_data;

	map_data = (t_dynarr){};
	if (!dynarr_init(&map_data, MAP_READ_CHUNK_SIZE, sizeof(char)))
		return (0);
	if (!mesh_init(empty)
		|| !read_map(&map_data, filepath)
		|| !parse_map(empty, &map_data))
	{
		dynarr_del(&map_data);
		mesh_del(empty);
		return (0);
	}
	dynarr_del(&map_data);
	center_mesh(empty);
	calculate_mesh_colors(empty);
	return (1);
}

int	mesh_init(t_mesh *empty)
{
	*empty = (t_mesh){};
	if (!dynarr_init(&empty->vertex_buffer, MIN_VERTS, sizeof(t_vertex)))
		return (0);
	return (1);
}

void	mesh_del(t_mesh *mesh)
{
	dynarr_del(&mesh->vertex_buffer);
}
