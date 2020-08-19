/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_chmod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 22:19:10 by tima              #+#    #+#             */
/*   Updated: 2020/08/19 15:45:56 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if ((st_mode & __S_IFMT) == __S_IFSOCK)
		return ('s');
	else
		return ('-');
}

void		display_chmod(t_file *tmp)
{
	char res[11];

	res[0] = get_type(tmp->sb.st_mode);
	res[1] = (tmp->sb.st_mode & S_IRUSR) ? 'r' : '-';
	res[2] = (tmp->sb.st_mode & S_IWUSR) ? 'w' : '-';
	if (tmp->sb.st_mode & S_ISUID)
		res[3] = (tmp->sb.st_mode & S_IXUSR) ? 's' : 'S';
	else
		res[3] = (tmp->sb.st_mode & S_IXUSR) ? 'x' : '-';
	res[4] = (tmp->sb.st_mode & S_IRGRP) ? 'r' : '-';
	res[5] = (tmp->sb.st_mode & S_IWGRP) ? 'w' : '-';
	if (tmp->sb.st_mode & S_ISGID)
		res[6] = (tmp->sb.st_mode & S_IXGRP) ? 's' : 'S';
	else
		res[6] = (tmp->sb.st_mode & S_IXGRP) ? 'x' : '-';
	res[7] = (tmp->sb.st_mode & S_IROTH) ? 'r' : '-';
	res[8] = (tmp->sb.st_mode & S_IWOTH) ? 'w' : '-';
	if (tmp->sb.st_mode & __S_ISVTX)
		res[9] = (tmp->sb.st_mode & S_IXOTH) ? 't' : 'T';
	else
		res[9] = (tmp->sb.st_mode & S_IXOTH) ? 'x' : '-';
	res[10] = ' ';
	write(1, res, 11);
}
