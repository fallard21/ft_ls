/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/07/27 14:46:56 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		find_key(char key)
{
	const char	*keys;
	int			i;

	keys = KEYS;
	i = 0;
	while (keys[i])
	{
		if (keys[i] == key)
			return (1);
		i++;
	}
	return (0);
}

int		init_keys(t_ls *ls, char *argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (!(find_key(argv[i])))
			return (argv[i]);
		ls->key_l = (argv[i] == 'l') ? 1 : ls->key_l;
		ls->key_up_r = (argv[i] == 'R') ? 1 : ls->key_up_r;
		ls->key_a = (argv[i] == 'a') ? 1 : ls->key_a;
		ls->key_r = (argv[i] == 'r') ? 1 : ls->key_r;
		ls->key_t = (argv[i] == 't') ? 1 : ls->key_t;
		i++;
	}
	return (0);
}

int		parse_args_to_keys(t_ls *ls, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_strncmp("--", av[i], 2) == 0)
		{
			if (ft_strcmp("--", av[i]) == 0)
				break ;
			else
				print_error(ls, av[i], 2);
		}
		if (av[i][0] == '-' && ft_strcmp(av[i], "-"))
		{
			ls->flag_keys = 1;	// ?
			if (init_keys(ls, av[i]))
				print_error(ls, av[i], 1);
		}
	}
	return (0);
}

int		parse_args_to_file(t_ls *ls, int ac, char **av)
{
	t_file	**tmp;
	int		i;
	int		flag;

	flag = 0;
	tmp = &ls->args;
	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp("--", av[i]) == 0)
			flag = 1;
		else if (av[i][0] != '-' || flag == 1 || !ft_strcmp("-", av[i]))
		{
			ls->flag_args = 1;
			if (lstat(av[i], &ls->sb) < 0)
				ft_printf(ACCESS, av[i], strerror(errno));
			else
			{
				if (!(*tmp = new_file(ls, "./", av[i])))
					return (free_list(&ls->args));
				tmp = &(*tmp)->next;
			}
		}
	}
	return (0);
}
