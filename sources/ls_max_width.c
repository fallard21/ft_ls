/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_max_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 06:30:43 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 00:26:32 by tima             ###   ########.fr       */
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

size_t	width_gid_uid(t_file *head, int flag)
{
	size_t max;
	size_t len;

	max = 0;
	while (head)
	{
		if (flag == 1)	// gid
			len = ft_strlen(head->gid_name);
		else			// uid
			len = ft_strlen(head->uid_name);
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
			len = get_uint_size(head->blocks, 0);
		if (len > max)
			max = len;
		head = head->next;
	}
	return (max);
}
