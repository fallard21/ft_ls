/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 01:24:23 by fallard           #+#    #+#             */
/*   Updated: 2020/06/19 21:25:30 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		copy_line(char **line, char **hist)
{
	int		i;
	char	*tmp;
	char	*n;

	i = 0;
	tmp = *hist;
	if ((n = ft_strchr(tmp, '\n')))
	{
		while (tmp[i] != '\n')
			i++;
		*line = ft_strsub(tmp, 0, i);
		*hist = ft_strdup(n + 1);
		ft_memdel((void**)&tmp);
	}
	else
	{
		*line = ft_strdup(*hist);
		ft_memdel((void**)&(*hist));
	}
	return (1);
}

int		get_line(t_gnl *list, char **line)
{
	char	*tmp;
	int		ret;
	char	buf[BUFF_SIZE + 1];

	while ((ret = read(list->fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!list->content)
			list->content = ft_strnew(0);
		tmp = list->content;
		list->content = ft_strjoin(tmp, buf);
		ft_memdel((void**)&tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (!list->content || list->content[0] == '\0'))
		return (0);
	return (copy_line(line, &list->content));
}

t_gnl	*new_list(const int fd)
{
	t_gnl	*new;

	new = ft_memalloc(sizeof(t_gnl));
	if (!new)
		return (NULL);
	new->fd = fd;
	return (new);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*hist;
	t_gnl			*tmp;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || (read(fd, buf, 0) < 0) || BUFF_SIZE < 1)
		return (-1);
	if (!hist)
		hist = new_list(fd);
	tmp = hist;
	while (tmp->fd != fd)
	{
		if (!tmp->next)
			if (!(tmp->next = new_list(fd)))
				return (-1);
		tmp = tmp->next;
	}
	return (get_line(tmp, line));
}
