/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:50 by fallard           #+#    #+#             */
/*   Updated: 2020/08/09 22:07:48 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	get_data(t_ls *ls, t_file *args, char *path, char *dir)
{
	t_data	res;
	t_file *tmp;

	ft_memset(&res, 0, sizeof(t_data));
	ft_memset(res.path, 0, LSPATH);
	if (!path)
		ft_strcat(res.path, dir);
	else
	{
		ft_strcat(res.path, path);
		ft_strcat(res.path, "/");
		ft_strcat(res.path, dir);
	}
	fix_path(res.path);
	if (!args && dir)
		res.head = get_dir_files(ls, res.path);
	else
		res.head = args;
	res.size = list_size(res.head);	// optimize
	res.width = get_width_arr(res.head);
	lstat(res.path, &ls->sb);
	if (errno == EACCES)
		print_error(ls, res.path, 4);
	tmp = res.head;
	while (tmp)
	{
		if (S_ISBLK(tmp->sb.st_mode) || S_ISCHR(tmp->sb.st_mode))
			res.spec_file = 1;
		tmp = tmp->next;
	}
	return (res);
}

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

//	run_ls(ls, NULL, "./");

void	run_ls(t_ls *ls, char *path, char *dirname)
{
	t_data root;

	if (ls->flag_args)
		root = get_data(ls, ls->args, NULL, NULL);
	else
		root = get_data(ls, NULL, "", ".");
	
	
	if (ls->flag_args)
	{
		display_file_from_args(ls, &root);
	}
	else
		display_files(ls, root);
	
	free_data(&root);
	//ls_print_dir(ls, root.head->name);
}

void	test_ls(t_ls *ls, char *path, char *dirname)
{
	//t_data root;

	//root = get_data(ls, NULL, path, dirname);

	//display_files(ls, root);

	//if (ls->key_up_r)
	//	test_ls(ls, dirname, root.head->name);
	//free_data(&root);

	display_dir(ls, path, dirname);
}

void	display_dir(t_ls *ls, char *path, char *name)
{
	t_data	data;
	t_file	*tmp;

	data = get_data(ls, NULL, path, name);
	data.head = sort(ls, data.head);
	display_path(ls, data);
	if ((ls->key_l || ls->key_s) && errno != EACCES)
		print_total(data.head);
	display_files(ls, data);
	tmp = data.head;
	while (tmp && ls->key_up_r)
	{
		if (S_ISDIR(tmp->sb.st_mode) && ft_strcmp(".", tmp->name) && ft_strcmp("..", tmp->name))
			display_dir(ls, tmp->path, tmp->name);
		tmp = tmp ->next;
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
