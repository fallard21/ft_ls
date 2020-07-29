/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:20:22 by fallard           #+#    #+#             */
/*   Updated: 2020/07/30 01:52:50 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_users(t_ls *ls, t_file *tmp, int *width)
{
	if (!ls->key_g)
		ft_printf("%-*s ", width[3], tmp->uid_name);	//g
	if (!ls->key_o)
		ft_printf("%-*s ", width[4], tmp->gid_name);	//o
}

void	display_size(t_file *f, int *width)
{
	if (S_ISREG(f->sb.st_mode) || S_ISDIR(f->sb.st_mode) ||
		S_ISLNK(f->sb.st_mode))
		ft_printf("%*ld ", 8, f->sb.st_size);
	else
		ft_printf("%3d, %3d ", major(f->sb.st_rdev), minor(f->sb.st_rdev));
}

void	display_time(time_t time_)
{
	char	*str;
	time_t	now;
	time_t	six;

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

void	display_name(t_ls *ls, t_file *current)
{
	if (S_ISLNK(current->sb.st_mode))
		print_link(current);
	else
		ft_printf("{3}%s{0}\n", current->name);
}

void	print_link(t_file *file)
{
	char	*buf;
	t_stat	sb;
	size_t	size;

	if (lstat(file->path, &sb) == -1)
		return ;
	size = sb.st_size + 1;
	if (!sb.st_size)
		size = PATH_MAX;
	if (!(buf = ft_calloc(size, sizeof(char))))
		return ;
	if (readlink(file->path, buf, size) < 0)
	{
		free(buf);
		write(1, "NONE\n", 5); // DEL
		return ;
	}
	ft_printf("{3}%s -> %s{0}\n", file->name, buf);
	ft_memdel((void**)&buf);
}
