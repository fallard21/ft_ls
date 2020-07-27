/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:25:15 by fallard           #+#    #+#             */
/*   Updated: 2020/07/27 14:27:27 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	choosing_ls(t_ls *ls)
{
	if (ls->flag_args == 0)
	{
		if (!(ls->args = get_dir_files(ls, "./")))
			return ;
	}
	do_ls(ls, ls->args);
}

void	do_ls(t_ls *ls, t_file *head)
{
	if (!head)
		return ;
	if (ls->key_t)
		head = sort_list(cmp_mtime, head);
	else
		head = sort_list(cmp_name, head);
	if (ls->key_r)
		head = reverse_list(head);
	
	if (ls->key_l || ls->key_s)
		print_total(head);
	if (ls->key_l)
		print_key_l(ls, head);
	else
		print_column(ls, head);
	free_list(&head);
}

void	print_total(t_file *head)
{
	long	blck;
	char	buf[50];
	char	*num;

	ft_memset(buf, 0, 50);
	blck = 0;
	while (head)
	{
		blck = blck + (head->sb.st_blocks / 2);
		head = head->next;
	}
	if (!(num = ft_ulong_itoa(blck, 1)))
		return ;
	ft_strcat(buf, "Total ");
	ft_strcat(buf, num);
	ft_strcat(buf, "\n");
	write(1, buf, ft_strlen(buf));
	free(num);
}
