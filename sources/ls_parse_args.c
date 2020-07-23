/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/07/23 06:45:03 by fallard          ###   ########.fr       */
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

int		parse_keys(t_ls *ls, char *argv)
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

void	parse_keys_args(t_ls *ls, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strncmp("--", argv[i], 2) == 0)
		{
			if (ft_strcmp("--", argv[i]) == 0)
				break ;
			else
			{
				ft_printf("ls: invalid parameter - '%s'\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
		if (argv[i][0] == '-')
		{
			ls->flag_keys = 1;
			if (parse_keys(ls, argv[i]))
			{
				ft_printf("ls: invalid key - '%c'\n", parse_keys(ls, argv[i]));
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	parse_file_args(t_ls *ls, int argc, char **argv)
{
	t_file	**tmp;
	int		i;
	int		flag;

	flag = 0;
	tmp = &ls->args;
	i = 0;
	while (++i < argc)
	{
		if (strcmp("--", argv[i]) == 0)
			flag = 1;
		else if (argv[i][0] != '-' || flag == 1)
		{
			ls->flag_args = 1;
			if (lstat(argv[i], &ls->sb) < 0)
				ft_printf(ACCESS, argv[i], strerror(errno));
			else
			{
				if (!(*tmp = new_file(ls, "./", argv[i])))
					return ;
				tmp = &(*tmp)->next;
			}
		}
	}
}

void	choosing_ls(t_ls *ls)
{
	if (ls->flag_args == 0 && ls->flag_keys == 0)
		ls_without_args(ls);
	else if (ls->flag_args == 0 && ls->flag_keys == 1)
		ls_only_keys(ls);
	else if (ls->flag_args == 1 && ls->flag_keys == 0)
		ls_only_args(ls);
	else if (ls->flag_args == 1 && ls->flag_keys == 1)
		//ls_keys_and_args(ls);
		;
}

void	ls_only_keys(t_ls *ls)
{
	t_file	*head;

	if (!(head = get_dir_files(ls, "./")))
		return ;	// ??
	head = sort_list(cmp_name, head);
	print_ls(ls, head);
	free_list(&head);
}

char	*print_link(t_ls *ls, char *file)
{
	char	*buf;
	t_stat	sb;
	size_t	size;

	if (lstat(file, &sb) == -1)
		return (NULL);
	size = sb.st_size + 1;
	if (!size)
		size = PATH_MAX;
	if (!(buf = ft_calloc(size, sizeof(char))))
		return (NULL);
	if (readlink(file, buf, size) < 0)
	{
		free(buf);
		return (NULL);
	}
	ft_printf("{3}%s -> %s{0}\n", file, buf);
	return (buf);
}
