/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:21:18 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:21:21 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	la_multiple(t_floats *flt, int exp)
{
	int	*tmp;
	int	i;

	flt->len_s = INTEGER_PART;
	if (!(flt->first = ft_memalloc(sizeof(int) * (flt->len_s))))
		exit(1);
	if (!(tmp = ft_memalloc(sizeof(int) * (flt->len_s))))
		exit(1);
	i = 0;
	pow_of_2(tmp, flt->len_s, exp);
	while (flt->mant[i] && exp >= 0)
	{
		if (flt->mant[i] == '1')
			addition_tab_rev(flt->first, tmp, flt->len_s);
		division_by_2(tmp, flt->len_s);
		exp--;
		i++;
	}
	free(tmp);
	part_after_dot(flt, i);
}

void	pow_of_2(int *res, int size, int pow)
{
	int i;
	int tmp;
	int p;

	pow = pow - 1;
	res[0] = (pow == -1) ? 1 : 2;
	p = 0;
	while (p < pow)
	{
		i = 0;
		tmp = 0;
		while (i < size)
		{
			tmp = 2 * res[i] + tmp;
			res[i] = tmp % 10000;
			tmp = tmp / 10000;
			i++;
		}
		p++;
	}
}

void	division_by_2(int *tab, int size)
{
	int i;
	int tmp;

	tmp = 0;
	i = 0;
	while (i < size)
	{
		if (i != size - 1 && tab[i + 1] % 2 != 0)
			tmp = (tab[i] + 10000) / 2 + tmp;
		else
			tmp = tab[i] / 2 + tmp;
		tab[i] = tmp % 10000;
		tmp = tmp / 10000;
		i++;
	}
}

void	addition_tab_rev(int *dst, int *src, int size)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	while (i < size)
	{
		tmp = (dst[i] + src[i]) + tmp;
		dst[i] = tmp % 10000;
		tmp = tmp / 10000;
		i++;
	}
}
