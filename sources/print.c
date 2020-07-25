/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/07/25 19:38:25 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("file_name: {2}%s{0}\n", head->name);
		ft_printf("inode: %lu\n", head->sb.st_ino);
		ft_printf("blocks: %ld\n", head->sb.st_blocks);
		ft_printf("nlink: %lu\n", head->sb.st_nlink);
		ft_printf("mode: %u\n", head->sb.st_mode);
		put_chmod(head->sb.st_mode); printf("\n");
		ft_printf("st_uid: %u\n", head->sb.st_uid);
		//ft_printf("name_uid: %s\n", head->uid_name);
		ft_printf("st_gid: %u\n", head->sb.st_gid);
		//ft_printf("name_gid: %s\n", head->gid_name);
		ft_printf("f_size: %ld\n", head->sb.st_size);
		
		ft_printf("mtime: %ld, msec %lu\n", head->sb.st_mtime, head->sb.st_mtim.tv_nsec);
		put_time(head->sb.st_mtime); ft_printf("\n\n");
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
		put_chmod(head->sb.st_mode);
		ft_printf("%*lu ", width[2], head->sb.st_nlink);
		ft_printf("%*s ", width[3], head->uid_name);
		ft_printf("%*s ", width[4], head->gid_name);
		ft_printf("%*ld ", width[5], head->sb.st_size);
		put_time(head->sb.st_mtime);
		ft_printf("{2}%s{0}\n", head->name);
		head = head->next;
	}
	free(width);
}

