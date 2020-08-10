/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:25:15 by fallard           #+#    #+#             */
/*   Updated: 2020/08/11 01:34:16 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_ls(t_ls *ls)
{
	t_data root;

	if (ls->flag_args)
	{
		root = get_data(ls, ls->args, NULL, "");
		display_file_from_args(ls, &root);
	}
	else
		display_dir(ls, NULL, "./");
}

void	display_dir(t_ls *ls, char *path, char *name)
{
	t_data	data;
	t_file	*tmp;

	data = get_data(ls, NULL, path, name);
	data.head = sort(ls, data.head);
	display_path(ls, data);
	display_total(ls, data.head);
	display_files(ls, data);
	tmp = data.head;
	while (tmp && ls->key_up_r)
	{
		if (S_ISDIR(tmp->sb.st_mode) && ft_strcmp(".", tmp->name)
			&& ft_strcmp("..", tmp->name))
			display_dir(ls, tmp->path, tmp->name);
		tmp = tmp->next;
	}
	free_data(&data);
}
