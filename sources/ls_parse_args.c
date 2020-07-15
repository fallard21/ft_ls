/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/07/15 05:00:51 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parse_args(t_ls *ls, int argc, char **argv)
{
	int		wkey;
	int		i;
	
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && (wkey = parse_keys(ls, argv[i])) != 0)
		{
			ft_printf("ls: invalid key - < %c >\n", wkey);
			exit(EXIT_FAILURE);
		}
		ft_printf("< %s >\n", argv[i++]);
	}
}

int		parse_keys(t_ls *ls, char *keys)	// ?
{
	int i;

	i = 1;
	while (keys[i])
	{
		if (keys[i] == 'l')
			ls->key_l = 1;
		else if (keys[i] == 'R')
			ls->key_R = 1;
		else if (keys[i] == 'a')
			ls->key_a = 1;
		else if (keys[i] == 'r')
			ls->key_r = 1;
		else if (keys[i] == 't')
			ls->key_t = 1;
		else
			return (keys[i]);
		i++;
	}
	return (0);
}

void	parse_keys_args(t_ls *ls, int argc, char **argv)
{
	int		i;
	char	key;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			ls->flag_keys = 1;
			if ((key = parse_keys(ls, argv[i])))
			{
				ft_printf("ls: invalid key - '%c'\n", key);
				exit (EXIT_FAILURE);
			}
		}
		//ft_printf("argv: %s\n", argv[i]);
		//ft_printf("status stat: %d\n", stat(argv[i], &ls->sb));
		i++;
	}
	ft_printf("key l: %d\n", ls->key_l);
	ft_printf("key R: %d\n", ls->key_R);
	ft_printf("key a: %d\n", ls->key_a);
	ft_printf("key r: %d\n", ls->key_r);
	ft_printf("key t: %d\n", ls->key_t);
}

void	parse_file_args(t_ls *ls, int argc, char **argv)
{
	t_file	**tmp;
	int		i;
	
	tmp = &ls->args;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			ls->flag_args = 1;
			if (stat(argv[i], &ls->sb) < 0)
				ft_printf("ls: cannot access %s: %s\n", argv[i], strerror(errno));
			else
			{
				*tmp = new_file(ls, argv[i]);
				tmp = &(*tmp)->next;
			}
		}
		i++;
	}
	print_list(ls->args);
}

void	choosing_ls(t_ls *ls)
{
	if (ls->flag_args == 0 && ls->flag_keys == 1)
		ls_only_keys(ls);
	else if (ls->flag_args == 1 && ls->flag_keys == 0)
		;
	else if (ls->flag_args == 1 && ls->flag_keys == 1)
		;
	
}

void	ls_only_keys(t_ls *ls)
{
	t_file 	*head;
	
	if (!(head = ls_read_dir(ls, ".")))
		return ;	// ??
	print_ls(ls, head);
}
