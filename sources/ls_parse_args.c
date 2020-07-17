/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:10:19 by tima              #+#    #+#             */
/*   Updated: 2020/07/17 03:33:23 by fallard          ###   ########.fr       */
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
	/*
	ft_printf("key l: %d\n", ls->key_l);
	ft_printf("key R: %d\n", ls->key_R);
	ft_printf("key a: %d\n", ls->key_a);
	ft_printf("key r: %d\n", ls->key_r);
	ft_printf("key t: %d\n", ls->key_t);
	*/
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
			if (lstat(argv[i], &ls->sb) < 0)
				ft_printf("ls: cannot access '%s': %s\n", argv[i], strerror(errno));
			else
			{
				*tmp = new_file(ls, argv[i]);
				tmp = &(*tmp)->next;
			}
		}
		i++;
	}
	//print_list(ls->args);
}

void	choosing_ls(t_ls *ls)
{
	if (ls->flag_args == 0 && ls->flag_keys == 1)
		ls_only_keys(ls);
	else if (ls->flag_args == 1 && ls->flag_keys == 0)
		ls_only_args(ls);
	else if (ls->flag_args == 1 && ls->flag_keys == 1)
		;
	
}

void	ls_only_keys(t_ls *ls)
{
	t_file 	*head;
	
	if (!(head = ls_read_dir(ls, ".")))
		return ;	// ??
	print_ls(ls, head);
	free_list(&head);
}

void	ls_only_args(t_ls *ls)
{
	t_file *tmp;

	print_link(ls, ls->args->name);
	ls->args = sort_list(cmp_name, ls->args);
	tmp = ls->args;
	ls_print_reg(tmp);
	while (tmp)
	{
		if (S_ISDIR(tmp->mode))
			ls_print_dir(ls, tmp->name);
		tmp = tmp->next;
	}
}

void	ls_print_dir(t_ls *ls, char *dir_name)
{
	t_file	*head;

	if (!(head = ls_read_dir(ls, dir_name)))
		ft_printf("ls: cannot open directory '%s': Permission denied");
	else
		ft_printf("\n{2}%s:{0}\n", dir_name);
	head = sort_list(cmp_name,  head);
	while (head)
	{
		if (head->name[0] != '.')
			ft_printf("%s  ", head->name);
		head = head->next;
	}
	ft_printf("\n");
}

void	ls_print_reg(t_file *head)
{
	int flag;

	flag = 0;
	while (head)
	{
		if (S_ISREG(head->mode) || S_ISLNK(head->mode))
		{
			flag = 1;
			ft_printf("%s  ", head->name);
		}
		head = head->next;	
	}
	if (flag)
		write(1, "\n\n", 2);
}

char *print_link(t_ls *ls, char *file)
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
		free (buf);
		return (NULL);
	}
	ft_printf("{3}%s -> %s{0}\n", file, buf);
	return (buf);
}
