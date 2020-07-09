/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:20:15 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:20:17 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_d(t_printf *pf)
{
	intmax_t	n;
	char		*str;

	n = specifier(pf);
	if (!(str = ft_ulong_itoa(dec_abs(n), dec_mod(n))))
		exit(1);
	if (!(n == 0 && !pf->prec))
	{
		if (n >= 0)
			put_pozitive_d(pf, &str);
		else
			put_negative_d(pf, &str);
	}
	else
	{
		put_zero_number(pf);
		free(str);
	}
}

void	put_pozitive_d(t_printf *pf, char **str)
{
	char	*s;
	int		len;

	s = flag_pos_prec(pf, str);
	if (pf->zero && pf->prec <= 0 && !pf->minus)
		s = zero_positive_flag(pf, &s);
	len = ft_strlen(s);
	if (!pf->minus)
		print_width(0, len, pf);
	ft_putstr(s);
	if (pf->minus)
		print_width(0, len, pf);
	free(s);
	pf->tmp = (pf->width > len) ? pf->width : len;
	pf->len = pf->len + ((pf->tmp > pf->prec) ? pf->tmp : pf->prec);
}

void	put_negative_d(t_printf *pf, char **str)
{
	char	*s;
	int		len;

	s = flag_neg_prec(pf, str);
	if (pf->zero && pf->prec <= 0 && !pf->minus)
		s = zero_negative_flag(pf, &s);
	len = ft_strlen(s);
	if (!pf->minus)
		print_width(0, len, pf);
	ft_putstr(s);
	if (pf->minus)
		print_width(0, len, pf);
	free(s);
	pf->tmp = (pf->width > len) ? pf->width : len;
	pf->len = pf->len + ((pf->tmp > pf->prec) ? pf->tmp : pf->prec);
}

void	put_zero_number(t_printf *pf)
{
	if (pf->plus && pf->minus)
		ft_putchar('+');
	ft_putnchar(' ', pf->width - pf->plus);
	if (pf->plus && !pf->minus)
		ft_putchar('+');
	pf->tmp = (pf->width > pf->prec) ? pf->width : pf->prec;
	if (!pf->width && !pf->prec && pf->plus)
		pf->tmp = 1;
	pf->len = pf->len + pf->tmp;
}
