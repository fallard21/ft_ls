/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_max_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 06:30:43 by tima              #+#    #+#             */
/*   Updated: 2020/08/10 00:50:37 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
size_t	width_nlink_size(t_file *head, int flag)
{
	size_t max;
	size_t len;

	max = 0;
	while (head)
	{
		if (flag == 1)	// nlink
			len = get_uint_size(head->sb.st_nlink, 0);
		else if (flag == 2)			// size
			len = get_uint_size(head->sb.st_size, 0);
		else if (flag == 2)			// inode
			len = get_uint_size(head->sb.st_size, 0);
		else if (flag == 2)			// block
			len = get_uint_size(head->sb.st_size, 0);
		else if (flag == 2)			// major
			len = get_uint_size(head->sb.st_size, 0);
		else if (flag == 2)			// minor
			len = get_uint_size(head->sb.st_size, 0);
		if (len > max)
			max = len;
		head = head->next;
	}
	return (max);
}

size_t	width_uid_gid(t_file *head, int flag)
{
	size_t max;
	size_t len;

	max = 0;
	while (head)
	{
		if (flag == 1)	// uid
			len = ft_strlen(head->uid_name);
		else			// gid
			len = ft_strlen(head->gid_name);
		if (len > max)
			max = len;
		head = head->next;
	}
	return (max);
}

size_t	width_ino_blck(t_file *head, int flag)
{
	size_t max;
	size_t len;

	max = 0;
	while (head)
	{
		if (flag == 1)	// inode
			len = get_uint_size(head->sb.st_ino, 0);
		else			// blocks
			len = get_uint_size(head->sb.st_blocks / 2, 0);
		if (len > max)
			max = len;
		head = head->next;
	}
	return (max);
}
*/

int		*get_width_arr(t_file *head)
{
	int *arr;

	if (!(arr = ft_calloc(8, sizeof(int))))
		ft_exit("malloc");
	while (head)
	{
		ls_max(width_num(head->sb.st_ino), &arr[0]);
		ls_max(width_num(head->sb.st_blocks), &arr[1]);
		ls_max(width_num(head->sb.st_nlink), &arr[2]);
		ls_max(ft_strlen(head->uid_name), &arr[3]);
		ls_max(ft_strlen(head->gid_name), &arr[4]);
		ls_max(width_num(head->fmajor), &arr[5]);
		ls_max(width_num(head->fminor), &arr[6]);
		ls_max(width_num(head->sb.st_size), &arr[7]);
		head = head ->next;
	}
	return (arr);
}

int		width_num(size_t num)
{
	int i;

	i = 0;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

void	ls_max(int current, int *width)
{
	if (current > *width)
		*width = current;
}
