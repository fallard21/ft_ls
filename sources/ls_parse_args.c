/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 04:50:46 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parse_args(t_ls *ls, int argc, char **argv)
{
	int			wkey;
	int			i;
	
	i = 1;
	while(i < argc)
	{
		if (argv[i][0] == '-' && (wkey = parse_keys(ls, argv[i])) != 0)
		{
			ft_printf("ls: invalid key - < %c >\n", wkey);
			exit(EXIT_FAILURE);
		}
		else
		{	
			;
		}
		ft_printf("< %s >\n", argv[i++]);
	}

	
}

int		parse_keys(t_ls *ls, char *keys)
{
	int i;

	i = 1;
	while(keys[i])
	{
		if (keys[i] == 'l')
			ls->flag_l = 1;
		else if (keys[i] == 'R')
			ls->flag_R = 1;
		else if (keys[i] == 'a')
			ls->flag_a = 1;
		else if (keys[i] == 'r')
			ls->flag_r = 1;
		else if (keys[i] == 't')
			ls->flag_t = 1;
		else
			return (keys[i]);
		i++;
	}
	if (!ls->flag)
		ls->flag += FLAGS;
	return (0);
}


void	parse_flag_args(t_ls *ls, int argc, char **argv)
{
	int		i;
	char	key;

	i = 1;
	while(i < argc)
	{
		if (argv[i][0] == '-')
		{
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
	ft_printf("key l: %d\n", ls->flag_l);
	ft_printf("key R: %d\n", ls->flag_R);
	ft_printf("key a: %d\n", ls->flag_a);
	ft_printf("key r: %d\n", ls->flag_r);
	ft_printf("key t: %d\n", ls->flag_t);
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
