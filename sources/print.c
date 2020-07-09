/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 00:23:52 by tima             ###   ########.fr       */
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
		put_chmod(head->mode);
		ft_printf("st_uid: %u\n", head->uid);
		ft_printf("name_uid: %s\n", head->uid_name);
		ft_printf("st_gid: %u\n", head->gid);
		ft_printf("name_gid: %s\n", head->gid_name);
		ft_printf("f_size: %ld\n", head->size);
		
		ft_printf("__time: %ld\n", head->ctime);
		put_time(head->ctime);
		//ft_printf("TIME: %k\n", head->time);
		//ft_printf("___dev: %lu\n", head->dev);
		head = head->next;
	}
	ft_printf("\n");
}
