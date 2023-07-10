/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:38:25 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/12 10:14:44 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

static char	*buf_get_line(t_dynarr *buf)
{
	char *const	src = (char *)buf->ptr;
	char *const	eol = ft_memchr(src, '\n', buf->size);
	char		*str;
	size_t		len;

	if (!buf->ptr || !buf->size || !eol)
		return (NULL);
	len = eol - src + 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, src, len);
	str[len] = '\0';
	buf->size -= len;
	if (buf->size)
		ft_memcpy(src, eol + 1, buf->size);
	return (str);
}

static char	*buf_to_str(t_dynarr *buf)
{
	char *const	src = buf->ptr;
	char		*str;

	str = malloc(buf->size + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, src, buf->size);
	str[buf->size] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static int		last_fd = -1;
	static t_dynarr	buf = (t_dynarr){0};
	char			*str;
	ssize_t			read_size;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	if (fd != last_fd && !dynarr_init(&buf, BUFFER_SIZE, sizeof(char)))
		return (NULL);
	last_fd = fd;
	str = NULL;
	read_size = BUFFER_SIZE;
	while (read_size > 0)
	{
		str = buf_get_line(&buf);
		if (str)
			return (str);
		read_size = dynarr_read(&buf, fd, BUFFER_SIZE);
	}
	if (buf.size)
		str = buf_to_str(&buf);
	last_fd = -1;
	dynarr_del(&buf);
	return (str);
}
