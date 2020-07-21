/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/07/17 20:37:27 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("file_name: {2}%s{0}\n", head->name);
		ft_printf("inode: %lu\n", head->inode);
		ft_printf("blocks: %ld\n", head->blocks);
		ft_printf("nlink: %lu\n", head->nlink);
		ft_printf("mode: %u\n", head->mode);
		put_chmod(head->mode); printf("\n");
		ft_printf("st_uid: %u\n", head->uid);
		ft_printf("name_uid: %s\n", head->uid_name);
		ft_printf("st_gid: %u\n", head->gid);
		ft_printf("name_gid: %s\n", head->gid_name);
		ft_printf("f_size: %ld\n", head->size);
		
		ft_printf("__time: %ld\n", head->ctime);
		put_time(head->ctime); ft_printf("\n\n");
		//ft_printf("TIME: %k\n", head->time);
		//ft_printf("___dev: %lu\n", head->dev);
		head = head->next;
	}
	ft_printf("\n");
}

void	print_ls(t_ls *ls, t_file *head)
{
	//head = sort_list(cmp_name, head);
	int *width;

	width  = get_width_arr(head);
	while (head)
	{
		//ft_printf("%*lu ",  width[0], head->inode);
		//ft_printf("%*ld ",  width[1], head->blocks / 2);
		put_chmod(head->mode);
		ft_printf("%*lu ", width[2], head->nlink);
		ft_printf("%*s ", width[3], head->uid_name);
		ft_printf("%*s ", width[4], head->gid_name);
		ft_printf("%*ld ", width[5], head->size);
		put_time(head->ctime);
		ft_printf("{2}%s{0}\n", head->name);
		head = head->next;
	}
	free(width);
}

