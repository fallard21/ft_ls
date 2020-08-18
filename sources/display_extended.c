/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:20:22 by fallard           #+#    #+#             */
/*   Updated: 2020/08/18 21:59:13 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_users(t_ls *ls, t_file *head, int *width)
{
	if (!ls->key_g)
		ft_printf("%-*s", width[3] + 1, head->uid_name);
	if (!ls->key_o)
		ft_printf("%-*s", width[4] + 1, head->gid_name);
}

void	display_size(t_data data, t_file *f, int *width)
{
	if (data.spec_file)
		width[7] = width[5] + 2 + 3;
	if (S_ISBLK(f->sb.st_mode) || S_ISCHR(f->sb.st_mode))
		ft_printf("%*d, %*d ", width[5], major(f->sb.st_rdev), \
		width[6], minor(f->sb.st_rdev));
	else
		ft_printf("%*ld ", width[7], f->sb.st_size);
}

void	display_time(t_ls *ls, t_file *tmp)
{
	char	*str;
	time_t	time_;
	time_t	now;
	time_t	six;

	if (ls->key_c)
		time_ = tmp->sb.st_ctime;
	else if (ls->key_u)
		time_ = tmp->sb.st_atime;
	else
		time_ = tmp->sb.st_mtime;
	now = time(NULL);
	six = 15778465;
	str = ctime(&time_);
	ft_printf("%-4.3s", str + 4);
	ft_printf("%-3.2s", str + 8);
	if (now - time_ > six || time_ > now)
		ft_printf("%5.4s ", str + 20);
	else
		ft_printf("%-6.5s", str + 11);
}

void	display_name(t_file *file)
{
	write(1, file->name, ft_strlen(file->name));
	if (S_ISLNK(file->sb.st_mode))
	{
		if (file->link)
		{
			write(1, " -> ", 4);
			write(1, file->link, ft_strlen(file->link));
		}
	}
	write(1, "\n", 1);
}
