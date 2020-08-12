/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_bonus_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:01:28 by fallard           #+#    #+#             */
/*   Updated: 2020/08/12 04:13:28 by fallard          ###   ########.fr       */
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

static int	get_sum_width(t_ls *ls, t_col *col, int row)
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

int			get_row(t_ls *ls, t_data *data)
{
	t_col	*col;
	int		i;
	int		row;

	col = &data->col;
	row = 1;
	i = 1;
	while (i++ <= col->size)
	{
		col->prev = col->col;
		col->m = col->size % row;
		col->col = (col->size / row) + ((col->m == 0) ? 0 : 1);
		col->width = get_sum_width(ls, col, row) +
			(2 * (col->col - 1)) + (col->space * col->col);
		if (col->prev == col->col)
		{
			row++;
			continue;
		}
		if (col->width < ls->tty_width)
			return (row);
		row++;
	}
	return (row);
}

static void	print_ib(t_ls *ls, t_data *data, int j)
{
	if (ls->key_i)
		ft_printf("%*lu ", data->width[0], data->col.ib[j]);
	if (ls->key_s)
		ft_printf("%*ld ", data->width[1], data->col.ib[j + data->size]);
}

void		print_column(t_ls *ls, t_data *data, t_col *col, int row)
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
				print_ib(ls, data, j);
				ft_printf("%-*s", width, col->args[j]);
				if (n-- > 0)
					write(1, "  ", 2);
			}
			j = j + row;
		}
		write(1, "\n", 1);
	}
}
