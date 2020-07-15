/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_max_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 06:30:43 by tima              #+#    #+#             */
/*   Updated: 2020/07/15 06:06:52 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		max_int_width(size_t num)
{
	int size;

	size = 0;
	while(num)
	{
		num = num / 10;
		size++;
	}
	return (size);
}

size_t	width_nlink_size(t_file *head, int flag)
{
	size_t max;
	size_t len;

	max = 0;
	while (head)
	{
		if (flag == 1)	// nlink
			len = get_uint_size(head->nlink, 0);
		else			// size
			len = get_uint_size(head->size, 0);
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
			len = get_uint_size(head->inode, 0);
		else			// blocks
			len = get_uint_size(head->blocks / 2, 0);
		if (len > max)
			max = len;
		head = head->next;
	}
	return (max);
}

int		*get_width_arr(t_file *head)
{
	int *arr;

	if (!(arr = ft_calloc(6, sizeof(int))))
		return (NULL);
	arr[0] = width_ino_blck(head, 1);
	arr[1] = width_ino_blck(head, 2);
	arr[2] = width_nlink_size(head, 1);
	arr[3] = width_uid_gid(head, 1);
	arr[4] = width_uid_gid(head, 2);
	arr[5] = width_nlink_size(head, 2);
	return (arr);
}
