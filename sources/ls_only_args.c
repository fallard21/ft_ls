/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:03:56 by fallard           #+#    #+#             */
/*   Updated: 2020/07/27 15:22:35 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_ls_args(t_ls *ls, t_file *head)
{
	t_file *tmp;

	//print_link(ls, ls->args->name);
	tmp = head;
	ls_print_reg(tmp);
	while (tmp)
	{
		if (S_ISDIR(tmp->sb.st_mode))
			ls_print_dir(ls, tmp->name);
		tmp = tmp->next;
	}
    free_list(&ls->args);
}

void	ls_print_dir(t_ls *ls, char *dir_name)
{
	t_file	*head;

	if (!(head = get_dir_files(ls, dir_name)))
		ft_printf("ls: cannot open directory '%s': Permission denied");
	else
		ft_printf("\n{2}%s:{0}\n", dir_name);
	head = sort_list(cmp_name,  head);
	print_column(ls, head);
    free_list(&head);
}

void	ls_print_reg(t_file *head)
{
	int flag;

	flag = 0;
	while (head)
	{
		if (S_ISREG(head->sb.st_mode) || S_ISLNK(head->sb.st_mode))
		{
			flag = 1;
			ft_printf("%s  ", head->name);
		}
		head = head->next;	
	}
	if (flag)
		write(1, "\n\n", 2);
}
