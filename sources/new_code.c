/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:50 by fallard           #+#    #+#             */
/*   Updated: 2020/08/09 23:59:43 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	*update_data(t_ls *ls, t_data **upd, t_file *new)
{
	if (!new)
		return (NULL);
	ft_memdel((void**)&(*upd)->width);
	(*upd)->head = new;
	(*upd)->size = list_size(new);
	(*upd)->width = get_width_arr(new);
	(*upd)->spec_file = 0;
	return (*upd);
}

void	test_ls(t_ls *ls, char *path, char *dirname)
{
	
	display_dir(ls, path, dirname);
}

void	display_dir(t_ls *ls, char *path, char *name)
{
	t_data	data;
	t_file	*tmp;

	data = get_data(ls, NULL, path, name);
	data.head = sort(ls, data.head);
	display_path(ls, data);
	display_total(ls, data.head);
	display_files(ls, data);
	tmp = data.head;
	while (tmp && ls->key_up_r)
	{
		if (S_ISDIR(tmp->sb.st_mode) && ft_strcmp(".", tmp->name)
			&& ft_strcmp("..", tmp->name))
			display_dir(ls, tmp->path, tmp->name);
		tmp = tmp->next;
	}
	free_data(&data);
}

void	display_path(t_ls *ls, t_data data)
{
	if ((ls->key_up_r || ls->flag_args) && errno != EACCES)
	{
		if (!ls->flag_path)
			ft_printf("{2}%s:{0}\n", data.path);
		else
			ft_printf("\n{2}%s:{0}\n", data.path);
		ls->flag_path = 1;
	}
}

void	fix_path(char *path)
{
	char	buf[LSPATH];
	int		len;
	int		i;
	int		j;
	int		flag;

	ft_strcpy(buf, path);
	ft_memset(path, 0, LSPATH);
	i = 0;
	j = 0;
	len = ft_strlen(buf);
	while (i < len)
	{
		if (buf[i] == '/')
			flag = 0;
		while (buf[i] && buf[i] != '/')
		{
			path[j++] = buf[i++];
			flag = 1;
		}
		if (flag)
			path[j++] = '/';
		i++;
	}
	path[j - 1] = '\0';
}
