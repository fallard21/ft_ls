/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:03:56 by fallard           #+#    #+#             */
/*   Updated: 2020/08/15 04:48:22 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	split_list(t_file **dirs, t_file **others, t_file **head)
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

static void	print_fargs(t_ls *ls, t_file *files)
{
	t_data	d_files;

	d_files = get_data(ls, files, NULL, "");
	d_files.head = sort(ls, d_files.head);
	display_files(ls, d_files);
	free_data(&d_files);
}

static void	print_dargs(t_ls *ls, t_file *dirs)
{
	t_data	d_dirs;

	d_dirs = get_data(ls, dirs, NULL, "");
	d_dirs.head = sort(ls, d_dirs.head);
	dirs = d_dirs.head;
	while (dirs)
	{
		display_dir(ls, dirs->path, dirs->name);
		dirs = dirs->next;
	}
	free_data(&d_dirs);
}

void		display_arguments(t_ls *ls, t_file *root)
{
	t_file	*dirs;
	t_file	*files;

	dirs = NULL;
	files = NULL;
	split_list(&dirs, &files, &root);
	if (files)
		print_fargs(ls, files);
	if (dirs && files)
		write(1, "\n", 1);
	if (dirs)
		print_dargs(ls, dirs);
}
