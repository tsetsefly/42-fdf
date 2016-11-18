/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 16:37:15 by dtse              #+#    #+#             */
/*   Updated: 2016/10/12 16:37:16 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_overflow	*content_detective(const int fd, t_list **file_list_ptr)
{
	t_list			*file_list;
	t_overflow		file_info;

	file_list = *file_list_ptr;
	while (file_list)
	{
		if (((t_overflow *)(file_list->content))->fd == fd)
			return (file_list->content);
		file_list = file_list->next;
	}
	file_info.fd = fd;
	if (!(file_info.buffer = ft_strnew(BUFF_SIZE + 1)))
		return (NULL);
	if (!(file_list = ft_lstnew(&file_info, sizeof(t_overflow))))
		return (NULL);
	ft_lstadd(file_list_ptr, file_list);
	return ((*file_list_ptr)->content);
}

static void			memory_detective(t_list **begin_list, int fd)
{
	t_list			*t;

	if (*begin_list)
	{
		if (((t_overflow *)((*begin_list)->content))->fd == fd)
		{
			t = (*begin_list);
			(*begin_list) = (*begin_list)->next;
			free(((t_overflow *)(t->content))->buffer);
			free(t);
			memory_detective(begin_list, fd);
		}
		else
			memory_detective(&((*begin_list)->next), fd);
	}
}

static ssize_t		norm_sucks(t_overflow **file, char *buf, char ***line)
{
	*(*line) = ft_strjoin((*file)->buffer, buf);
	ft_bzero((*file)->buffer, ft_strlen((*file)->buffer));
	return (1);
}

static ssize_t		file_detective(t_overflow **file, const int fd,
	char ***line)
{
	char			*end;
	char			buf[BUFF_SIZE + 1];
	ssize_t			rtn_bytes;

	while ((rtn_bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rtn_bytes] = '\0';
		if (!(end = ft_strchr(buf, '\n')))
		{
			if (rtn_bytes < BUFF_SIZE && rtn_bytes > 0)
				return (norm_sucks(&(*file), buf, &(*line)));
			(*file)->buffer = (char *)ft_realloc((*file)->buffer,
				ft_strlen((*file)->buffer) + BUFF_SIZE + 1);
			(*file)->buffer = ft_strcat((*file)->buffer, buf);
		}
		else
		{
			*end = '\0';
			*(*line) = ft_strjoin((*file)->buffer, buf);
			(*file)->buffer = ft_strcpy((*file)->buffer, (end + 1));
			return (1);
		}
	}
	return (rtn_bytes);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*file_list;
	t_overflow		*file;
	ssize_t			rtn_bytes;
	char			*end;

	if (!line)
		return (-1);
	file = content_detective(fd, &file_list);
	if ((end = ft_strchr(file->buffer, '\n')))
	{
		*end = '\0';
		*line = ft_strdup(file->buffer);
		file->buffer = ft_strcpy(file->buffer, (end + 1));
		return (1);
	}
	rtn_bytes = file_detective(&file, fd, &line);
	if (ft_strlen(file->buffer) && rtn_bytes == 0)
	{
		*line = ft_strdup(file->buffer);
		ft_bzero(file->buffer, ft_strlen(file->buffer));
		return (1);
	}
	(rtn_bytes == 0) ? (memory_detective(&file_list, fd)) : (rtn_bytes);
	return (rtn_bytes);
}
