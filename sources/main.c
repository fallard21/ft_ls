/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:21:09 by tima              #+#    #+#             */
/*   Updated: 2020/07/16 09:35:39 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	sort_words(char **word, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while(i < (size - 1))
	{
		j = 0;
		while (j < (size - 1 - i))
		{
			if (ft_strcmp(word[j], word[j + 1]) > 0)
			{
				tmp = word[j];
				word[j] = word[j + 1];
				word[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_file	*ls_read_dir(t_ls *ls, char *dir_name)
{
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(dir_name)))
		return (NULL);
	while((ls->lol = readdir(ls->dir)))
	{
		if (!(*tmp = new_file(ls, ls->lol->d_name)))
		{
			closedir(ls->dir);
			return (NULL);	// ???
		}
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	return (head);
}

int		ls_without_args(t_ls *ls)
{	
	t_file	*tmp;

	if (!(ls->args = ls_read_dir(ls, ".")))
		return (1);
	ls->args = sort_list(cmp_name, ls->args);
	tmp = ls->args;
	while(tmp)
	{
		if (tmp->name[0] != '.')
			ft_printf("%s  ", tmp->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
	free_list(&ls->args);
	return (0);
}

t_file 	*new_file(t_ls *ls, char *name)
{
	t_file	*tmp;

	lstat(name, &ls->sb);
	ls->gr_gid = getgrgid(ls->sb.st_gid);
	ls->pw_uid = getpwuid(ls->sb.st_uid);
	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		return (NULL);
	tmp->inode = ls->sb.st_ino;
	tmp->name = ft_strdup(name);
	tmp->blocks = ls->sb.st_blocks;
	tmp->nlink = ls->sb.st_nlink;
	tmp->mode = ls->sb.st_mode;
	tmp->uid = ls->sb.st_uid;
	tmp->uid_name = ft_strdup(ls->pw_uid->pw_name);
	tmp->gid = ls->sb.st_gid;
	tmp->gid_name = ft_strdup(ls->gr_gid->gr_name);
	tmp->size = ls->sb.st_size;
	tmp->ctime = ls->sb.st_ctime;
	//tmp->dev = ls->sb.st_dev;
	// if (!tmp->name || tmp->uid_name || tmp->gid_name)
	// 	return (NULL);
	return (tmp);
}


int	main(int argc, char **argv)
{
	t_ls ls;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	if (argc == 1)
		ls_without_args(&ls);
	else
	{
		parse_keys_args(&ls, argc, argv);
		parse_file_args(&ls, argc, argv);
		//print_list(ls.args);
		choosing_ls(&ls);
		//ft_printf("{1}flag_args: %d{0}\n", ls.flag_args);
		//ft_printf("{1}flag_keys: %d{0}\n", ls.flag_keys);
	}
	return (0);
}
