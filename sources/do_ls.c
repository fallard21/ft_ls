/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:25:15 by fallard           #+#    #+#             */
/*   Updated: 2020/07/30 01:02:35 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	choosing_ls(t_ls *ls)
{
	do_ls(ls, ls->args, "./");
}

void	do_ls(t_ls *ls, t_file *head, char *dir)
{
	if (ls->flag_args == 0)
		head = get_dir_files(ls, NULL);
	else
		head = ls->args;
	if (!head)
		return ;
	
	head = sort(ls, head);
	//if (ls->key_l || ls->key_s)
	//	print_total(head);
	if (ls->flag_args)
		ls_print_args(ls, head);
	else
		main_print(ls, head); 
	//free_list(&head);
	
}

void	ls_print_args(t_ls *ls, t_file *head)
{
	t_file	*tmp;

	split_list(ls, head);
	tmp = ls->dirs;
	main_print(ls, ls->others);
	if (ls->dirs && ls->others)
		write(1, "\n", 1);
	while (tmp)
	{
		ls_print_dir(ls, tmp->name);
		if (tmp->next)
			write(1, "\n", 1);
		tmp = tmp->next;
	}
	//ls->flag_args = 0;
	free_list(&ls->dirs);
	free_list(&ls->others);
}

void	ls_print_dir(t_ls *ls, char *dir_name)
{
	t_file	*head;

	if (!(head = get_dir_files(ls, dir_name)))
		ft_printf("ls: cannot open directory '%s': Permission denied");
	else
		ft_printf("{2}%s:{0}\n", dir_name);
	head = sort(ls, head);
	if (ls->key_l || ls->key_s)
		print_total(head);
	main_print(ls, head);
	free_list(&head);
}

int		list_size(t_file *head)
{
	int count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

void	main_print(t_ls *ls, t_file *head)
{
	if (ls->key_l)
		print_key_l(ls, head);
	else
		print_column(ls, head);
}

void	split_list(t_ls *ls, t_file *head)
{
	t_file	**dir;
	t_file	**oth;
	t_file	*next;

	dir = &ls->dirs;
	oth = &ls->others;
	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		if (S_ISDIR(head->sb.st_mode))
		{
			*dir = head;
			(*dir)->next = NULL;
			dir = &(*dir)->next;
		}
		else
		{
			*oth = head;
			(*oth)->next = NULL;
			oth = &(*oth)->next;
		}
		head = next;
	}
}
