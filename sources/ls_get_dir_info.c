/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/08/09 04:31:32 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*get_dir_files(t_ls *ls, char *path, char *dir_name)
{
	t_file	*head;
	t_file	**tmp;
	char	fpath[PATH_MAX];

	ft_memset(fpath, 0, PATH_MAX);
	if (!path)
		ft_strcat(fpath, dir_name);
	else
	{
		ft_strcat(fpath, path);
		ft_strcat(fpath, "/");
		ft_strcat(fpath, dir_name);
	}
	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(fpath)))
		return (NULL);
	while((ls->lol = readdir(ls->dir)))
	{
		if (ls->lol->d_name[0] == '.' && ls->key_a == 0)
			continue;
		if (!(*tmp = new_file(ls, fpath, ls->lol->d_name)))
			break;
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	return (head);
}

t_file	*new_file(t_ls *ls, char *path, char *name)
{
	t_file	*tmp;
	t_stat	current;
	char *fpath;

	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		return (NULL);
	if (!path)
		ft_strcat(tmp->path, "");
	else
	{
		ft_strcat(tmp->path, path);
		ft_strcat(tmp->path, "/");
	}
	fpath = ft_strjoin(tmp->path, name);
	if (lstat(fpath, &current) == -1)
		perror("lstat");
	tmp->sb = current;
	tmp->fmajor = major(tmp->sb.st_rdev);
	tmp->fminor = minor(tmp->sb.st_rdev);
	tmp->name = ft_strdup(name);
	ls->gr_gid = getgrgid(current.st_gid);
	ls->pw_uid = getpwuid(current.st_uid);
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	if (!tmp->uid_name || !tmp->gid_name || !tmp->name)
	{
		free_list(&tmp);
		return (NULL);
	}
	free(fpath);
	return (tmp);
}
