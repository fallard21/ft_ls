/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:50 by fallard           #+#    #+#             */
/*   Updated: 2020/08/07 03:56:22 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	get_data(t_ls *ls, t_file *args, char *path, char *dir)
{
	t_data	res;
	t_file *tmp;

	ft_memset(&res, 0, sizeof(t_data));
	if (!args)
		res.head = get_dir_files(ls, dir);
	else
		res.head = args;
	res.size = list_size(res.head);	// optimize
	res.width = get_width_arr(res.head);
	tmp = res.head;
	while (tmp)
	{
		if (S_ISBLK(tmp->sb.st_mode) || S_ISCHR(tmp->sb.st_mode))
			res.spec_file = 1;
		tmp = tmp->next;
	}
	return (res);
}
