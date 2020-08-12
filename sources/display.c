/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 00:37:01 by fallard           #+#    #+#             */
/*   Updated: 2020/08/12 04:03:52 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_files(t_ls *ls, t_data data)
{
	if (ls->key_l)
		display_key_l(ls, data);
	else if (ls->key_one)
		display_one_column(ls, &data);
	else
		display_column(ls, &data);
}

void	display_key_l(t_ls *ls, t_data data)
{
	while (data.head)
	{
		if (ls->key_i)
			ft_printf("%*lu ", data.width[0], data.head->sb.st_ino);
		if (ls->key_s)
			ft_printf("%*ld ", data.width[1], data.head->sb.st_blocks / 2);
		display_chmod(data.head);
		ft_printf("%*lu ", data.width[2], data.head->sb.st_nlink);
		display_users(ls, data.head, data.width);
		display_size(data, data.head, data.width);
		display_time(ls, data.head);
		display_name(ls, data.head);
		data.head = data.head->next;
	}
}

void	display_one_column(t_ls *ls, t_data *data)
{
	t_file *tmp;

	tmp = data->head;
	while (tmp)
	{
		if (ls->key_i)
			ft_printf("%*lu ", data->width[0], tmp->sb.st_ino);
		if (ls->key_s)
			ft_printf("%*ld ", data->width[1], tmp->sb.st_blocks / 2);
		ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}
