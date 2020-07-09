/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:59:57 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 06:17:20 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_time(time_t time)
{
	char	**str;
	int i = 1;

	str = ft_strsplit(ctime(&time), ' ');
	
	while (i < 4)
	{
		ft_printf("%2.5s ", str[i]);
		i++;
	}
	free_split(&str);
}

void	print_ls(t_ls *ls, t_file *head)
{
	//head = sort_list(cmp_name, head);
	while (head)
	{
		put_chmod(head->mode);
		ft_printf("%2lu ", head->nlink);
		ft_printf("%s ", head->uid_name);
		ft_printf("%s ", head->gid_name);
		ft_printf("%5ld ", head->size);
		put_time(head->ctime);
		ft_printf("{2}%s{0}\n", head->name);
		head = head->next;
	}
	
}
