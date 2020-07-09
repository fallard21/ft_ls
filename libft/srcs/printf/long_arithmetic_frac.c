/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic_frac.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:07:02 by fallard           #+#    #+#             */
/*   Updated: 2020/02/18 21:07:28 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	part_after_dot(t_floats *flt, int i)
{
	int	*tmp_end;

	if (i == 64)
	{
		flt->len_e = 1;
		if (!(flt->end = ft_memalloc(sizeof(int) * flt->len_e)))
			exit(1);
		return ;
	}
	flt->len_e = FRACTION_MIN;
	if (!(flt->end = ft_memalloc(sizeof(int) * flt->len_e)))
		exit(1);
	if (!(tmp_end = ft_memalloc(sizeof(int) * flt->len_e)))
		exit(1);
	tmp_end[0] = 5000;
	while (flt->mant[i])
	{
		if (flt->mant[i] == '1')
			addition_fraction(flt->end, tmp_end, flt->len_e);
		pow_of_5(tmp_end, flt->len_e, 2);
		i++;
	}
	free(tmp_end);
}

void	la_division(t_floats *flt, int exp)
{
	int *tmp_end;
	int i;

	flt->len_e = FRACTION_MAX;
	if (!(tmp_end = ft_memalloc(sizeof(int) * flt->len_e)))
		exit(1);
	if (!(flt->end = ft_memalloc(sizeof(int) * flt->len_e)))
		exit(1);
	tmp_end[0] = 5000;
	pow_of_5(tmp_end, flt->len_e, exp);
	i = 0;
	while (flt->mant[i])
	{
		if (flt->mant[i] == '1')
			addition_fraction(flt->end, tmp_end, flt->len_e);
		pow_of_5(tmp_end, flt->len_e, 2);
		i++;
	}
	flt->len_s = 1;
	if (!(flt->first = ft_memalloc(sizeof(int) * flt->len_s)))
		exit(1);
	free(tmp_end);
}

void	pow_of_5(int *res, int size, int pow)
{
	int				i;
	int				j;
	int				p;
	unsigned int	tmp;

	pow = pow - 1;
	j = 1;
	p = 0;
	tmp = 0;
	while (p < pow)
	{
		i = size - 2;
		while (i >= 0)
		{
			tmp = 5000 * res[i];
			res[i + 1] = res[i + 1] + tmp % 10000;
			res[i] = tmp / 10000;
			i--;
		}
		p++;
		j++;
	}
}

void	addition_fraction(int *dst, int *src, int size)
{
	int i;
	int tmp;

	tmp = 0;
	i = size - 1;
	while (i >= 0)
	{
		tmp = dst[i] + src[i] + tmp;
		dst[i] = tmp % 10000;
		tmp = tmp / 10000;
		i--;
	}
}
