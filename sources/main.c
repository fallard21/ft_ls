/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:21:09 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 06:14:16 by tima             ###   ########.fr       */
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

int		without_args(t_ls *ls)
{	
	t_file	*head;
	t_file	**tmp;

	head = NULL;
	tmp = &head;
	if (!(ls->dir = opendir(".")))
		ft_exit();
	while((ls->lol = readdir(ls->dir)))
	{
		//ft_printf("off: %ld\n", ls->lol->d_off);
		//ft_printf("reclen: %hhu\n", ls->lol->d_reclen);
		//ft_printf("inode: %lu\n\n", ls->lol->d_ino);
		*tmp = new_file(ls, ls->lol->d_name);
		tmp = &(*tmp)->next;
	}
	closedir(ls->dir);
	//print_list(head);
	print_ls(ls, head);
	free_list(&head);
	return (0);
}

t_file 	*new_file(t_ls *ls, char *name)
{
	t_file	*tmp;

	stat(name, &ls->sb);
	//ft_printf("{1}file: %s, inode: %lu{0}\n", file->d_name, ls->sb.st_ino);
	ls->gr_gid = getgrgid(ls->sb.st_gid);
	ls->pw_uid = getpwuid(ls->sb.st_uid);
	if (!(tmp = ft_calloc(1, sizeof(t_file))))
		ft_exit();
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
	return (tmp);
}


int	main(int argc, char **argv)
{
	t_ls ls;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	if (argc == 1)
		without_args(&ls);
	else
	{
		parse_flag_args(&ls, argc, argv);
		parse_file_args(&ls, argc, argv);
	}
	
	return (0);
}
