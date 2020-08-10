/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:53:56 by fallard           #+#    #+#             */
/*   Updated: 2020/08/11 01:56:37 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_size(t_file *left, t_file *right)
{
	if (left->sb.st_size == right->sb.st_size)
		return (cmp_name(left, right));
	if (left->sb.st_size > right->sb.st_size)
		return (1);
	return (0);
}

int		cmp_name(t_file *left, t_file *right)
{
	if (ft_strcmp(left->name, right->name) < 0)
		return (1);
	return (0);
}

int		cmp_mtime(t_file *left, t_file *right)
{
	if (left->sb.st_mtime == right->sb.st_mtime)
	{
		if (left->sb.st_mtim.tv_nsec == right->sb.st_mtim.tv_nsec)
			return (cmp_name(left, right));
		if (left->sb.st_mtim.tv_nsec > right->sb.st_mtim.tv_nsec)
			return (1);
		return (0);
	}
	if (left->sb.st_mtime > right->sb.st_mtime)
		return (1);
	return (0);
}

int		cmp_ctime(t_file *left, t_file *right)
{
	if (left->sb.st_ctime == right->sb.st_ctime)
	{
		if (left->sb.st_ctim.tv_nsec == right->sb.st_ctim.tv_nsec)
			return (cmp_name(left, right));
		if (left->sb.st_ctim.tv_nsec > right->sb.st_ctim.tv_nsec)
			return (1);
		return (0);
	}
	if (left->sb.st_ctime > right->sb.st_ctime)
		return (1);
	return (0);
}

int		cmp_atime(t_file *left, t_file *right)
{
	if (left->sb.st_atime == right->sb.st_atime)
	{
		if (left->sb.st_atim.tv_nsec == right->sb.st_atim.tv_nsec)
			return (cmp_name(left, right));
		if (left->sb.st_atim.tv_nsec > right->sb.st_atim.tv_nsec)
			return (1);
		return (0);
	}
	if (left->sb.st_atime > right->sb.st_atime)
		return (1);
	return (0);
}
