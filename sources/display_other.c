/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/08/19 00:32:31 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_total(t_ls *ls, t_file *head)
{
	long	blck;
	char	buf[30];
	char	*num;

	if ((ls->key_l || ls->key_s) && ls->flag_perm == 0)
	{
		ft_memset(buf, 0, 30);
		blck = 0;
		while (head)
		{
			blck = blck + (head->sb.st_blocks / 2);
			head = head->next;
		}
		if ((num = ft_ulong_itoa(blck, 1)))
		{
			ft_strcat(buf, "total ");
			ft_strcat(buf, num);
			ft_strcat(buf, "\n");
			write(1, buf, ft_strlen(buf));
			ft_memdel((void**)&num);
		}
	}
}

void	display_error(t_ls *ls, char *file, int flag)
{
	ft_strclr(ls->buf);
	if (flag == NO_FILE)
	{
		write(2, "ls: cannot access '", 19);
		write(2, file, ft_strlen(file));
		write(2, "': ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	if (flag == DIR_PERM)
	{
		ft_strcat(ls->buf, "ls: cannot open directory '");
		ft_strcat(ls->buf, file);
		ft_strcat(ls->buf, "': Permission denied\n");
	}
	if (flag == LINK_PERM)
	{
		ft_strcat(ls->buf, "ls: cannot read symbolic link '");
		ft_strcat(ls->buf, file);
		ft_strcat(ls->buf, "': Permission denied\n");
	}
	write(2, ls->buf, ft_strlen(ls->buf));
}

void	error_exit(t_ls *ls, char *file, int flag)
{
	char str[LSPATH];

	ft_memset(str, 0, LSPATH);
	if (flag == BAD_KEY)
	{
		ft_strcat(str, "ls: invalid key - '");
		str[ft_strlen(str)] = init_keys(ls, file);
		ft_strcat(str, "'\n");
	}
	if (flag == BAD_PARAMETER)
	{
		ft_strcat(str, "ls: invalid parameter '");
		ft_strcat(str, file);
		ft_strcat(str, "'\n");
	}
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
