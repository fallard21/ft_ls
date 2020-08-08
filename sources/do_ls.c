/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:25:15 by fallard           #+#    #+#             */
/*   Updated: 2020/08/08 22:22:57 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	choosing_ls(t_ls *ls)
{
	do_ls(ls, ls->args, "./");
}

void	do_ls(t_ls *ls, t_file *head, char *dir)
{
	t_data	data;

	if (ls->flag_args)
		data = get_data(ls, ls->args, NULL, NULL);
	else
		data = get_data(ls, NULL, NULL, dir);
	
	data.head = sort(ls, data.head);

	if (ls->flag_args || ls->key_up_r)
		display_file_from_args(ls, &data);
	else
		display_files(ls, data); 

}

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

	/*
	//d = get_data(ls, dirs, NULL, NULL);
	tmp = root->head;
	if (dirs && others)
		write(1, "\n", 1);
	while (tmp)
	{
		ls_print_dir(ls, tmp->name);
		if (tmp->next)
			write(1, "\n", 1);
		tmp = tmp->next;
	}
	ls->flag_args = 0;
	*/
}


void	ls_print_dir(t_ls *ls, char *dir_name)
{
	t_data data;

	data = get_data(ls, NULL, "", dir_name);
	if (!data.head)
		ft_printf("ls: cannot open directory '%s': Permission denied\n", dir_name);
	else
		ft_printf("{2}%s:{0}\n", dir_name);
	data.head = sort(ls, data.head);
	if (ls->key_l || ls->key_s)
		print_total(data.head);
	display_files(ls, data);
	free_data(&data);
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

void	display_files(t_ls *ls, t_data data)
{
	if (ls->key_l)
		print_key_l(ls, data);
	else if (ls->key_one)
		print_one_column(data.head);
	else
		print_column(ls, data);
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
