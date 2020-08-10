/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/08/11 01:40:48 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	get_data(t_ls *ls, t_file *args, char *path, char *dir)
{
	t_data	res;
	t_file	*tmp;

	ft_memset(&res, 0, sizeof(t_data));
	init_path(res.path, path, dir, 1);
	fix_path(res.path);
	if (!args && dir)
		res.head = get_dir_files(ls, res.path);
	else
		res.head = args;
	res.size = list_size(res.head);
	res.width = get_width_arr(res.head);
	lstat(res.path, &ls->sb);
	if (errno == EACCES)
		display_error(res.path, 4);
	tmp = res.head;
	while (tmp)
	{
		if (S_ISBLK(tmp->sb.st_mode) || S_ISCHR(tmp->sb.st_mode))
			res.spec_file = 1;
		tmp = tmp->next;
	}
	return (res);
}

void	init_path(char *add, char *path, char *dir, int flag)
{
	if (flag == 1)
	{
		if (!path)
			ft_strcat(add, dir);
		else
		{
			ft_strcat(add, path);
			ft_strcat(add, dir);
		}
	}
	else
	{
		if (!path)
			ft_strcat(add, "");
		else
		{
			ft_strcat(add, path);
			ft_strcat(add, "/");
		}
	}
}

t_file	*get_dir_files(t_ls *ls, char *fpath)
{
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(fpath)))
		return (NULL);
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
	init_path(tmp->path, path, name, 2);
	if (!(fpath = ft_strjoin(tmp->path, name)))
		ft_exit(LMALLOC);
	if (lstat(fpath, &current) == -1)
		ft_exit(LLSTAT);
	tmp->sb = current;
	tmp->fmajor = major(tmp->sb.st_rdev);
	tmp->fminor = minor(tmp->sb.st_rdev);
	tmp->name = ft_strdup(name);
	ls->gr_gid = getgrgid(current.st_gid);
	ls->pw_uid = getpwuid(current.st_uid);
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	if (!tmp->uid_name || !tmp->gid_name || !tmp->name)
		ft_exit(LMALLOC);
	ft_strdel(&fpath);
	return (tmp);
}

int		list_size(t_file *head)
{
	int count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
