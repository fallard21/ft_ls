/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/07/25 18:17:49 by fallard          ###   ########.fr       */
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
	ft_strcat(ft_strcat(ft_strcat(tmp->path, dirname), "/"), filename);
	if (save_file_info(ls, tmp, filename))
			return (NULL);
	//tmp->dev = ls->sb.st_dev;
	return (tmp);
}

int		save_file_info(t_ls *ls, t_file *tmp, char *name)
{
	t_stat	current;

	if (lstat(tmp->path, &current) == -1)
		return (free_list(&tmp));
	tmp->sb = current;
	tmp->name = ft_strdup(name);

	ls->gr_gid = getgrgid(current.st_gid);
	ls->pw_uid = getpwuid(current.st_uid);
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	
	//tmp->mode = current.st_mode;
	/*
	if (ls->key_l)
	{
		tmp->inode = current.st_ino;
		tmp->blocks = current.st_blocks;
		tmp->nlink = current.st_nlink;
		tmp->size = current.st_size;
		tmp->mtime = current.st_mtime;
		ls->gr_gid = getgrgid(current.st_gid);
		ls->pw_uid = getpwuid(current.st_uid);
		tmp->uid = current.st_uid;
		
		tmp->gid = current.st_gid;
		
	}
	*/
	return (0);
}
