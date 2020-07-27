/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_chmod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 22:19:10 by tima              #+#    #+#             */
/*   Updated: 2020/07/27 15:31:00 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_chmod(mode_t mode)
{
	char res[11];

	res[0] = get_type(mode);

	res[1] = (mode & S_IRUSR) ? 'r' : '-';
	res[2] = (mode & S_IWUSR) ? 'w' : '-';
	res[3] = (mode & S_IXUSR) ? 'x' : '-';

	res[4] = (mode & S_IRGRP) ? 'r' : '-';
	res[5] = (mode & S_IWGRP) ? 'w' : '-';
	res[6] = (mode & S_IXGRP) ? 'x' : '-';

	res[7] = (mode & S_IROTH) ? 'r' : '-';
	res[8] = (mode & S_IWOTH) ? 'w' : '-';
	res[9] = (mode & S_IXOTH) ? 'x' : '-';
	res[10] = ' ';
	write(1, res, 11);
}

char	get_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('p');
	else if ((mode & __S_IFMT) == __S_IFSOCK)
		return ('s');
	else
		return ('-');
}
