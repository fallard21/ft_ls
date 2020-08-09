/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/08/09 21:14:22 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("file_name: {2}%s{0}\n", head->name);
		ft_printf("inode: %lu\n", head->sb.st_ino);
		ft_printf("blocks: %ld\n", head->sb.st_blocks);
		ft_printf("nlink: %lu\n", head->sb.st_nlink);
		ft_printf("mode: %u\n", head->sb.st_mode);
		display_chmod(head); printf("\n");
		ft_printf("st_uid: %u\n", head->sb.st_uid);
		//ft_printf("name_uid: %s\n", head->uid_name);
		ft_printf("st_gid: %u\n", head->sb.st_gid);
		//ft_printf("name_gid: %s\n", head->gid_name);
		ft_printf("f_size: %ld\n", head->sb.st_size);
		
		ft_printf("mtime: %ld, msec %lu\n", head->sb.st_mtime, head->sb.st_mtim.tv_nsec);
		display_time(head->sb.st_mtime); ft_printf("\n\n");
		//ft_printf("TIME: %k\n", head->time);
		//ft_printf("___dev: %lu\n", head->dev);
		head = head->next;
	}
	ft_printf("\n");
}
*/

void	print_key_l(t_ls *ls, t_data data)
{
	while (data.head)
	{
		if (ls->key_i)
			ft_printf("%*lu ", data.width[0], data.head->sb.st_ino);
		if (ls->key_s)
			ft_printf("%*ld ", data.width[1], data.head->sb.st_blocks / 2);
		display_chmod(data.head);
		ft_printf("%*lu ", data.width[2], data.head->sb.st_nlink);
		display_users(ls, data.head, data.width);
		display_size(data, data.head, data.width);
		display_time(ls, data.head);
		display_name(ls, data.head);
		data.head = data.head->next;
	}

}

void	print_total(t_file *head)
{
	long	blck;
	char	buf[30];
	char	*num;

	ft_memset(buf, 0, 30);
	blck = 0;
	while (head)
	{
		blck = blck + (head->sb.st_blocks / 2);
		head = head->next;
	}
	if (!(num = ft_ulong_itoa(blck, 1)))
		return ;
	ft_strcat(buf, "total ");
	ft_strcat(buf, num);
	ft_strcat(buf, "\n");
	write(1, buf, ft_strlen(buf));
	free(num);
}


void	print_error(t_ls *ls, char *file, int flag)
{
	char str[LSPATH];

	ft_memset(str, 0, LSPATH);
	if (flag == 1)
	{
		ft_strcat(str, "ls: invalid key - '");
		str[ft_strlen(str)] = init_keys(ls, file);
		ft_strcat(str, "'\n");
	}
	if (flag == 2)
	{
		ft_strcat(str, "ls: invalid parameter '");
		ft_strcat(str, file);
		ft_strcat(str, "'\n");
	}
	if (flag == 3)
	{
		ft_strcat(ft_strcat(str, "ls: "), file);
		ft_strcat(str, ": ");
		ft_strcat(str, strerror(errno));
		ft_strcat(str, "\n");
	}
	if (flag == 4)
	{
		ft_strcat(str, "ls: cannot open directory '");
		ft_strcat(str, file);
		ft_strcat(str, "': Permission denied\n");
	}
	write(2, str, ft_strlen(str));
	if (flag == 1 || flag == 2)
		exit(EXIT_FAILURE);
}

void	print_one_column(t_file *head)
{
	while (head)
	{
		ft_printf("%s\n", head->name);
		head = head->next;
	}
}
