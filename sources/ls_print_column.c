/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_column.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 09:11:23 by fallard           #+#    #+#             */
/*   Updated: 2020/07/27 14:05:12 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_max_width(t_col *col, int j, int row)
{
	int max;
	int i;

	max = 0;
	i = (int)(j / row) * row;
	max = col->lens[i];
	while (row--)
	{
		if (i >= col->size)
			break ;
		if (col->lens[i] > max)
			max = col->lens[i];
		i++;
	}
	return (max);
}


static int	get_sum_width(t_col *col, int row)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (i < col->size)
	{
		if (i < col->size)
			count = count + get_max_width(col, i, row);
		i = i + row;
	}
	return (count);
}

static int	*get_lens_of_args(t_col *col)
{
	int	*res;
	int i;

	i = 0;
	if (!(res = ft_calloc(col->size, sizeof(int))))
		return (NULL);
	while (i < col->size)
	{
		res[i] = ft_strlen(col->args[i]);
		i++;
	}
	return (res);
}

static char	**list_to_char(t_col *col, t_file *head)
{
	char	**res;
	t_file	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		col->size++;
		tmp = tmp->next;
	}
	if (!(res = ft_calloc(col->size + 1, sizeof(char*))))
		return (NULL);
	while (head)
	{
		if (!(res[i++] = ft_strdup(head->name)))
		{
			free_split(&res);
			return (NULL);
		}
		head = head->next;
	}
	return (res);
}

static int	get_row(t_ls *ls, t_col *col)
{
	int i;
	int row;

	row = 1;
	i = 1;
	while (i++ <= col->size)
	{
		col->prev = col->col;
		col->m = col->size % row;
		col->col = (col->size / row) + ((col->m == 0) ? 0 : 1);
		col->space = get_sum_width(col, row) + (2 * (col->col - 1));
		if (col->prev == col->col)
		{
			row++;
			continue;
		}
		if (col->space < ls->tty_width)
			return (row);
		row++;
	}
	return (row);
}

static void	print_col(t_col *col, int row)
{
	int i;
	int j;
	int width;
	int n;

	i = 0;
	while (i < row)
	{
		n = col->col - 1;
		j = i++;
		while (j < col->size)
		{
			if (j <= col->size)
			{
				width = (row == 1) ? 0 : get_max_width(col, j, row);
				ft_printf("%-*s", width, col->args[j]);
				if (n-- > 0)
					write(1, "  ", 2);
			}
			j = j + row;
		}
		write(1, "\n", 1);
	}
}

void	print_column(t_ls *ls, t_file *head)
{
	t_col	col;

	memset(&col, 0, sizeof(col));
	if (!head)
		return ;
	if (!(col.args = list_to_char(&col, head)))
		return ;
	if (!(col.lens = get_lens_of_args(&col)))
	{
		free_split(&col.args);
		return ;
	}
	col.row = get_row(ls, &col);
	print_col(&col, col.row);
	free(col.lens);
	free_split(&col.args);
}