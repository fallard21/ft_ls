/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/08/09 16:59:27 by fallard          ###   ########.fr       */
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
		ls->key_c = (argv[i] == 'c') ? 1 : ls->key_c;
		ls->key_u = (argv[i] == 'u') ? 1 : ls->key_u;
		ls->key_i = (argv[i] == 'i') ? 1 : ls->key_i;
		ls->key_s = (argv[i] == 's') ? 1 : ls->key_s;
		ls->key_up_s = (argv[i] == 'S') ? 1 : ls->key_up_s;
		ls->key_f = (argv[i] == 'f') ? 1 : ls->key_f;
		ls->key_o = (argv[i] == 'o') ? 1 : ls->key_o;
		ls->key_g = (argv[i] == 'g') ? 1 : ls->key_g;
		ls->key_one = (argv[i] == '1') ? 1 : ls->key_one;
		update_keys(ls, NULL, argv[i]);
		i++;
	}
	return (0);
}

void	update_keys(t_ls *ls, char *del, int key)
{
	if (key == 'o' || key == 'g')
		ls->key_l = 1;
	if (key == 'l')
		ls->key_one = 0;
	if (key == 'f')
	{
		ls->key_a = 1;
		ls->key_l = 0;
		ls->key_up_s = 0;
		ls->key_s = 0;
	}
	if (key == 'S')
	{
		ls->key_t = 0;
		ls->key_f = 0;
	}
	if (key == 'c')
		ls->key_u = 0;
	if (key == 'u')
		ls->key_c = 0;
	if (key == 't')
	{
		ls->key_f = 0;
		ls->key_up_s = 0;
	}
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
				print_error(ls, av[i], 3);
			else
			{
				if (!(*tmp = new_file(ls, NULL, av[i])))
					return (free_list(&ls->args));
				tmp = &(*tmp)->next;
			}
		}
	}
	return (0);
}
