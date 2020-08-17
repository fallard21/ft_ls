/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 06:30:43 by tima              #+#    #+#             */
/*   Updated: 2020/08/17 22:16:48 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	width_num(size_t num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static void	ls_max(int current, int *width)
{
	if (current > *width)
		*width = current;
}

int			*get_width_arr(t_file *head)
{
	int *arr;

	if (!(arr = ft_calloc(8, sizeof(int))))
		ft_exit(LMALLOC);
	while (head)
	{
		ls_max(width_num(head->sb.st_ino), &arr[0]);
		ls_max(width_num(head->sb.st_blocks), &arr[1]);
		ls_max(width_num(head->sb.st_nlink), &arr[2]);
		if (head->uid_name)
			ls_max(ft_strlen(head->uid_name), &arr[3]);
		if (head->gid_name)
			ls_max(ft_strlen(head->gid_name), &arr[4]);
		ls_max(width_num(head->fmajor), &arr[5]);
		ls_max(width_num(head->fminor), &arr[6]);
		ls_max(width_num(head->sb.st_size), &arr[7]);
		head = head->next;
	}
	return (arr);
}
