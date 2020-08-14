/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:00:04 by tima              #+#    #+#             */
/*   Updated: 2020/08/14 23:30:02 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_total(t_ls *ls, t_file *head)
{
	long	blck;
	char	buf[30];
	char	*num;

	if ((ls->key_l || ls->key_s) && errno != EACCES)
	{
		ft_memset(buf, 0, 30);
		blck = 0;
		while (head)
		{
			blck = blck + (head->sb.st_blocks / 2);
			head = head->next;
		}
		if (num = ft_ulong_itoa(blck, 1))
		{
			ft_strcat(buf, "total ");
			ft_strcat(buf, num);
			ft_strcat(buf, "\n");
			write(1, buf, ft_strlen(buf));
			ft_memdel((void**)&num);
		}
	}
}

void	display_path(t_ls *ls, char *fpath)
{
	fix_path(fpath);

	if ((ls->key_up_r || ls->flag_args))
	{
		if (ls->flag_args && ls->count_args == 1 && !ls->key_up_r)
			return ;
		if (!ls->flag_path)
			ft_printf("{2}%s:{0}\n", fpath);
		else
			ft_printf("\n{2}%s:{0}\n", fpath);
		ls->flag_path = 1;
	}
}

void	fix_path(char *path)
{
	char	buf[LSPATH];
	int		len;
	int		i;
	int		j;
	int		flag;

	ft_strcpy(buf, path);
	ft_strclr(path);
	i = 0;
	j = 0;
	flag = 0;
	len = ft_strlen(buf);
	while (i < len + 1)
	{
		if (buf[i] == '/')
			flag = 1;
		if (buf[i] != '/')
		{
			if (flag)
				path[j++] = '/';
			flag = 0;
			path[j++] = buf[i];
		}
		i++;
	}
}

void	display_error(char *file, int flag)
{
	char str[LSPATH];

	ft_memset(str, 0, LSPATH);
	if (flag == NO_FILE)
	{
		ft_strcat(ft_strcat(str, "ls: "), file);
		ft_strcat(str, ": ");
		ft_strcat(str, strerror(errno));
		ft_strcat(str, "\n");
	}
	if (flag == DIR_PERM)
	{
		ft_strcat(str, "ls: cannot open directory '");
		ft_strcat(str, file);
		ft_strcat(str, "': Permission denied\n");
	}
	if (flag == LINK_PERM)
	{
		ft_strcat(str, "ls: cannot read symbolic link '");
		ft_strcat(str, file);
		ft_strcat(str, "': Permission denied\n");
	}
	write(2, str, ft_strlen(str));
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
