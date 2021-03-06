/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/08/18 22:48:07 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	get_data(t_ls *ls, t_file *args, char *path, char *dir)
{
	t_data	res;

	ls->flag_perm = 0;
	ft_memset(&res, 0, sizeof(t_data));
	init_path(res.path, path, dir, 1);
	if (!args && dir)
		res.head = get_dir_files(ls, res.path);
	else
		res.head = args;
	res.size = list_size(&res);
	res.width = get_width_arr(res.head);
	return (res);
}

t_file	*get_dir_files(t_ls *ls, char *fpath)
{
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(fpath)))
	{
		ls->flag_perm = 1;
		display_error(ls, fpath, DIR_PERM);
		return (NULL);
	}
	display_path(ls, fpath);
	while ((ls->lread = readdir(ls->dir)))
	{
		if (ls->lread->d_name[0] == '.' && ls->key_a == 0)
			continue;
		if (!(*tmp = new_file(ls, fpath, ls->lread->d_name)))
			break ;
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	return (head);
}

t_file	*new_file(t_ls *ls, char *path, char *name)
{
	t_file	*tmp;
	t_stat	current;
	char	*fpath;

	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		return (NULL);
	if (!(tmp->name = ft_strdup(name)))
		ft_exit(LMALLOC);
	init_path(tmp->path, path, name, 2);
	if (!(fpath = ft_strjoin(tmp->path, name)))
		ft_exit(LMALLOC);
	if (lstat(fpath, &current) == -1)
		ft_exit(LLSTAT);
	tmp->sb = current;
	get_lstat(ls, tmp, fpath);
	ft_strdel(&fpath);
	return (tmp);
}

void	get_lstat(t_ls *ls, t_file *tmp, char *fpath)
{
	if (ls->key_l)
	{
		if (S_ISLNK(tmp->sb.st_mode))
			get_symbolic_link(ls, tmp, fpath);
		if (S_ISBLK(tmp->sb.st_mode) || S_ISCHR(tmp->sb.st_mode))
		{
			tmp->fmajor = major(tmp->sb.st_rdev);
			tmp->fminor = minor(tmp->sb.st_rdev);
		}
		ls->gr_gid = getgrgid(tmp->sb.st_gid);
		ls->pw_uid = getpwuid(tmp->sb.st_uid);
		if (!(tmp->uid_name = ft_strdup(ls->pw_uid->pw_name)))
			ft_exit(LMALLOC);
		if (!(tmp->gid_name = ft_strdup(ls->gr_gid->gr_name)))
			ft_exit(LMALLOC);
	}
}

void	get_symbolic_link(t_ls *ls, t_file *tmp, char *fpath)
{
	int size;

	size = tmp->sb.st_size;
	if (!tmp->sb.st_size)
		size = LSPATH;
	size = size + 1;
	if ((tmp->link = ft_calloc(size, sizeof(char))))
	{
		if (readlink(fpath, tmp->link, size) < 0)
		{
			display_error(ls, fpath, LINK_PERM);
			ft_memdel((void**)&tmp->link);
		}
	}
}
