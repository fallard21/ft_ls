/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/07/23 09:00:03 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*get_dir_files(t_ls *ls, char *dir_name)
{
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(dir_name)))
		return (NULL);
	while((ls->lol = readdir(ls->dir)))
	{
		if (ls->lol->d_name[0] == '.' && ls->key_a == 0)
			continue;
		if (!(*tmp = new_file(ls, dir_name, ls->lol->d_name)))
		{
			closedir(ls->dir);
			return (NULL);	// ???
		}
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	return (head);
}

t_file	*new_file(t_ls *ls, char *dirname, char *filename)
{
	t_file	*tmp;

	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		return (NULL);
	ft_strcat(tmp->path, dirname);
	ft_strcat(tmp->path, "/");
	ft_strcat(tmp->path, filename);
	if (lstat(tmp->path, &ls->sb) == -1)
	{
		free (tmp);
		return (NULL);
	}
	tmp->inode = ls->sb.st_ino;
	tmp->blocks = ls->sb.st_blocks;
	tmp->nlink = ls->sb.st_nlink;
	tmp->mode = ls->sb.st_mode;
	tmp->size = ls->sb.st_size;
	tmp->ctime = ls->sb.st_ctime;
	//tmp->dev = ls->sb.st_dev;
	if (save_filenames(ls, tmp, filename))
		return (NULL);
	return (tmp);
}

int		save_filenames(t_ls *ls, t_file *tmp, char *name)
{
	tmp->name = ft_strdup(name);
	ls->gr_gid = getgrgid(ls->sb.st_gid);
	ls->pw_uid = getpwuid(ls->sb.st_uid);
	tmp->uid = ls->sb.st_uid;
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid = ls->sb.st_gid;
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	if (!tmp->uid_name || !tmp->gid_name || !tmp->name)
		return (free_list(&tmp));
	return (0);
}
