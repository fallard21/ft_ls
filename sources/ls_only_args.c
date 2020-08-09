/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:03:56 by fallard           #+#    #+#             */
/*   Updated: 2020/08/10 00:46:56 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_file_from_args(t_ls *ls, t_data *root)
{
	t_file	*tmp;
	t_file	*dirs;
	t_file	*others;
	t_data	o;
	t_data	d;
	
	dirs = NULL;
	others = NULL;
	split_list(&dirs, &others, &root->head);
	root->head = dirs;
	o = get_data(ls, others, NULL, NULL);
	display_files(ls, o);
	update_data(ls, &root, dirs);
	if (dirs && others)
		write(1, "\n", 1);
	free_data(&o);
}

t_data	*update_data(t_ls *ls, t_data **upd, t_file *new)
{
	if (!new)
		return (NULL);
	ft_memdel((void**)&(*upd)->width);
	(*upd)->head = new;
	(*upd)->size = list_size(new);
	(*upd)->width = get_width_arr(new);
	(*upd)->spec_file = 0;
	return (*upd);
}

void	split_list(t_file **dirs, t_file **others, t_file **head)
{
	t_file	**dir;
	t_file	**oth;
	t_file	*next;

	dir = &(*dirs);
	oth = &(*others);
	while (*head)
	{
		next = (*head)->next;
		if (S_ISDIR((*head)->sb.st_mode))
		{
			*dir = *head;
			(*dir)->next = NULL;
			dir = &(*dir)->next;
		}
		else
		{
			*oth = *head;
			(*oth)->next = NULL;
			oth = &(*oth)->next;
		}
		*head = next;
	}
}
