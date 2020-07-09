/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_round_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:20:40 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:20:43 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	plus_one(t_floats *flt)
{
	int i;
	int tmp;

	i = flt->len_s - 1;
	tmp = 1;
	while (i > 0)
	{
		tmp = (flt->one[i] - 48) + tmp;
		flt->one[i] = (tmp % 10) + 48;
		tmp = tmp / 10;
		i--;
	}
}

int		plus_five(t_printf *pf, t_floats *flt)
{
	int i;
	int ost;

	pf->prec = (pf->prec < 0) ? 6 : pf->prec;
	if (pf->prec >= flt->len_e)
		return (0);
	i = pf->prec;
	ost = 5;
	if (flt->two[i] == '5')
	{
		if (check_five(flt, i + 1))
		{
			if ((flt->two[i - 1] - 48) % 2 == 0)
				return (0);
		}
	}
	while (i >= 0)
	{
		ost = (flt->two[i] - 48) + ost;
		flt->two[i] = (ost % 10) + 48;
		ost = ost / 10;
		i--;
	}
	return (ost);
}

int		check_five(t_floats *flt, int i)
{
	while (flt->two[i])
	{
		if (flt->two[i] != '0')
			return (0);
		i++;
	}
	return (1);
}
