/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:06:49 by fallard           #+#    #+#             */
/*   Updated: 2020/07/30 12:12:34 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*get_dir_files(t_ls *ls, char *dir_name)
{
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!dir_name)
		dir_name = "./";
	if (!(ls->dir = opendir(dir_name)))
		return (NULL);
	while((ls->lol = readdir(ls->dir)))
	{
		if (ls->lol->d_name[0] == '.' && ls->key_a == 0)
			continue;
		if (!(*tmp = new_file(ls, dir_name, ls->lol->d_name)))
		{
			closedir(ls->dir);
			free_list(&head);
			return (NULL);
		}
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	return (head);
}

t_file	*new_file(t_ls *ls, char *dirname, char *filename)
{
	t_file	*tmp;
	t_stat	current;

	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		return (NULL);
	if (dirname == NULL)
		ft_strcat(tmp->path, filename);
	else
	{
		ft_strcat(tmp->path, dirname);
		ft_strcat(tmp->path, "/");
		ft_strcat(tmp->path, filename);
	}
	if (lstat(tmp->path, &current) == -1)
		perror("lstat");
	tmp->sb = current;
	tmp->name = ft_strdup(filename);
	ls->gr_gid = getgrgid(current.st_gid);
	ls->pw_uid = getpwuid(current.st_uid);
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	if (!tmp->uid_name || !tmp->gid_name || !tmp->name)
	{
		free_list(&tmp);
		return (NULL);
	}
	return (tmp);
}
