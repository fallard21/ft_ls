/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 02:22:49 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 00:19:54 by tima             ###   ########.fr       */
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
	if (left->size > right->size)
		return (1);
	return (0);
}

int		cmp_name(t_file *left, t_file *right)
{
	if (ft_strcmp(left->name, right->name) < 0)
		return (1);
	return (0);
}

int		cmp_time(t_file *left, t_file *right)
{
	if (left->ctime < right->ctime)
		return (1);
	return (0);
}
