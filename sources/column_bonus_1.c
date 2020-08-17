/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_bonus_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 09:11:23 by fallard           #+#    #+#             */
/*   Updated: 2020/08/18 02:04:50 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		*get_lens_of_args(t_col *col)
{
	int	*res;
	int i;

	i = 0;
	if (!(res = ft_calloc(col->size, sizeof(int))))
		ft_exit(LMALLOC);
	while (i < col->size)
	{
		res[i] = ft_strlen(col->args[i]);
		i++;
	}
	return (res);
}

static char		**list_to_char(t_data *data)
{
	char	**res;
	t_file	*tmp;
	int		i;

	i = 0;
	tmp = data->head;
	data->col.size = data->size;
	if (!(res = ft_calloc(data->col.size + 1, sizeof(char*))))
		ft_exit(LMALLOC);
	while (tmp)
	{
		if (!(res[i++] = ft_strdup(tmp->name)))
			ft_exit(LMALLOC);
		tmp = tmp->next;
	}
	return (res);
}

static size_t	*ino_blck_to_arr(t_data *data)
{
	size_t	*arr;
	t_file	*tmp;
	int		i;

	tmp = data->head;
	i = 0;
	arr = ft_calloc(data->size * 2, sizeof(size_t));
	if (!arr)
		ft_exit(LMALLOC);
	while (tmp)
	{
		arr[i] = tmp->sb.st_ino;
		arr[i + data->size] = tmp->sb.st_blocks / 2;
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void			display_column(t_ls *ls, t_data *data)
{
	if (!data->head)
		return ;
	if (ls->key_i)
		data->col.space = data->col.space + data->width[0] + 1;
	if (ls->key_s)
		data->col.space = data->col.space + data->width[1] + 1;
	data->col.args = list_to_char(data);
	data->col.lens = get_lens_of_args(&data->col);
	data->col.ib = ino_blck_to_arr(data);
	data->col.row = get_row(ls, data);
	if (data->col.col == 1)
		display_one_column(ls, data);
	else
		print_column(ls, data, &data->col, data->col.row);
	free_col(&data->col);
}
