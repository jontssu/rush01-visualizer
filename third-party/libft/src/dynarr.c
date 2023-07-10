/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:10:38 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:34:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	dynarr_init(t_dynarr *arr, size_t size, size_t type_size)
{
	if (!arr || !size || !type_size)
		return (0);
	if (arr->ptr)
		dynarr_del(arr);
	arr->ptr = malloc(size * type_size);
	arr->size = 0;
	if (arr->ptr)
	{
		arr->type_size = type_size;
		arr->cap = size;
		ft_bzero(arr->ptr, arr->cap * arr->type_size);
		return (1);
	}
	arr->type_size = 0;
	arr->cap = 0;
	return (0);
}

void	dynarr_del(t_dynarr *arr)
{
	if (arr->ptr)
		free(arr->ptr);
	arr->ptr = NULL;
	arr->type_size = 0;
	arr->size = 0;
	arr->cap = 0;
}

int	dynarr_resize(t_dynarr *arr, size_t new_cap)
{
	unsigned char	*tmp;

	if (!arr || !arr->ptr)
		return (0);
	if (new_cap == arr->cap)
		return (1);
	tmp = malloc(new_cap * arr->type_size);
	if (!tmp)
		return (0);
	if (new_cap < arr->size)
	{
		ft_memcpy(tmp, arr->ptr, new_cap * arr->type_size);
		arr->size = new_cap;
	}
	else
		ft_memcpy(tmp, arr->ptr, arr->size * arr->type_size);
	free(arr->ptr);
	arr->ptr = tmp;
	arr->cap = new_cap;
	return (1);
}

int	dynarr_pushback(t_dynarr *arr, void *type_data, size_t count)
{
	void	*dst;

	while (arr->size + count > arr->cap)
	{
		if (!dynarr_resize(arr, 2 * arr->cap))
			return (0);
	}
	dst = (unsigned char *)arr->ptr + (arr->size * arr->type_size);
	ft_memcpy(dst, type_data, count * arr->type_size);
	arr->size += count;
	return (1);
}

ssize_t	dynarr_read(t_dynarr *arr, int fd, size_t bytes)
{
	size_t			byte_cap;
	size_t			byte_size;
	ssize_t			read_size;
	void			*dst;

	byte_size = arr->size * arr->type_size;
	byte_cap = arr->cap * arr->type_size;
	while (byte_size + bytes > byte_cap)
	{
		if (dynarr_resize(arr, 2 * arr->cap))
		{
			byte_size = arr->size * arr->type_size;
			byte_cap = arr->cap * arr->type_size;
		}
		else
			return (-1);
	}
	dst = (unsigned char *)arr->ptr + byte_size;
	read_size = read(fd, dst, bytes);
	if (read_size > 0)
		arr->size += read_size;
	return (read_size);
}
