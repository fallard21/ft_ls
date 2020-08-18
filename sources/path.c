/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:25:31 by fallard           #+#    #+#             */
/*   Updated: 2020/08/18 21:52:01 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_path(t_ls *ls, char *fpath)
{
	fix_path(fpath);
	if ((ls->key_up_r || ls->flag_args))
	{
		if (ls->flag_args && ls->count_args == 1 && !ls->key_up_r)
			return ;
		if (!ls->flag_path)
			ft_printf("%s:\n", fpath);
		else
			ft_printf("\n%s:\n", fpath);
		ls->flag_path = 1;
	}
}

void	init_path(char *add, char *path, char *dir, int flag)
{
	if (flag == 1)
	{
		if (!path)
			ft_strcat(add, dir);
		else
		{
			ft_strcat(add, path);
			ft_strcat(add, dir);
		}
	}
	else
	{
		if (!path)
			ft_strcat(add, "");
		else
		{
			ft_strcat(add, path);
			ft_strcat(add, "/");
		}
	}
	fix_path(add);
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
