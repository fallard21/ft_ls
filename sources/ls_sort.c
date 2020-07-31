/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 02:22:49 by tima              #+#    #+#             */
/*   Updated: 2020/07/31 16:02:44 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*sort_list(int (*cmp)(t_file*, t_file*), t_file *head)
{
	t_file	*new_head;
	t_file	*tmp;
	t_file	*current;

	new_head = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (!new_head || cmp(tmp, new_head))
		{
			tmp->next = new_head;
			new_head = tmp;
		}
		else
		{
			current = new_head;
			while (current->next && !(cmp(tmp, current->next)))
				current = current->next;
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	return (new_head);
}

t_file	*reverse_list(t_file *head)
{
	t_file	*prev;
	t_file	*right;

	prev = NULL;
	right = head->next;
	while (right)
	{
		head->next = prev;
		prev = head;
		head = right;
		right = right->next;
	}
	head->next = prev;
	return (head);
}

int		cmp_size(t_file *left, t_file *right)
{
	if (left->sb.st_size == right->sb.st_size)
		return(cmp_name(left, right));
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
			return(cmp_name(left, right));
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
			return(cmp_name(left, right));
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
			return(cmp_name(left, right));
		if (left->sb.st_atim.tv_nsec > right->sb.st_atim.tv_nsec)
			return (1);
		return (0);
	}
	if (left->sb.st_atime > right->sb.st_atime)
		return (1);
	return (0);
}

t_file	*sort(t_ls *ls, t_file *head)
{
	if (ls->key_f)
		return (head);

	if (ls->key_t)
	{
		if (ls->key_c)
			head = sort_list(cmp_ctime, head);
		else if (ls->key_u)
			head = sort_list(cmp_atime, head);
		else
			head = sort_list(cmp_mtime, head);
	}
	else
		head = sort_list(cmp_name, head);
	if (ls->key_r)
		head = reverse_list(head);
	return (head);
}
