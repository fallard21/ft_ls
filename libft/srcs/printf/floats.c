/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:19:02 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 00:28:28 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_f(t_printf *pf)
{
	t_double_l	n;
	t_ldbl_cast	dbl;
	char		*str;
	int			len;

	n = (pf->spec == 'L') ? va_arg(pf->args, t_double_l) :
		(t_double_l)va_arg(pf->args, double);
	dbl.d = n;
	if (valide_float(dbl) != 0)
		return (error_f(pf, dbl));
	str = get_long_float(pf, dbl, n);
	str = (n < 0) ? str : float_pos_treatment(pf, &str);
	if (pf->zero && !pf->minus)
		str = float_zero_treatment(pf, &str);
	len = ft_strlen(str);
	if (!pf->minus)
		print_width(0, len, pf);
	ft_putstr(str);
	if (pf->minus)
		print_width(0, len, pf);
	free(str);
	pf->tmp = (pf->width > len) ? pf->width : len;
	pf->len = pf->len + pf->tmp;
}

char	*get_long_float(t_printf *pf, t_ldbl_cast dbl, t_double_l n)
{
	t_floats	*flt;
	char		*res;
	int			exp;

	if (!(flt = create_struct()))
		exit(1);
	res = NULL;
	if (n == 0)
		float_n_zero(flt);
	else
	{
		if (!(flt->mant = base2(dbl.t_parts.mantissa)))
			exit(1);
		exp = dbl.t_parts.exponent - 16383;
		if (exp < 0)
			la_division(flt, dec_abs(exp));
		else
			la_multiple(flt, exp);
	}
	res = parts_join(dbl, flt, pf);
	pf_free_floats(flt);
	return (res);
}

void	float_n_zero(t_floats *flt)
{
	flt->len_s = 1;
	flt->len_e = 1;
	if (!(flt->first = ft_memalloc(sizeof(int) * flt->len_s)))
		exit(1);
	if (!(flt->end = ft_memalloc(sizeof(int) * flt->len_e)))
		exit(1);
}

char	*float_pos_treatment(t_printf *pf, char **str)
{
	char	*res;
	int		flag;
	int		len;

	len = ft_strlen(*str);
	flag = 0;
	if (pf->plus || pf->space)
		flag = 1;
	if (!(res = ft_memalloc(sizeof(char) * (len + flag + 1))))
		exit(1);
	ft_strcpy(res + flag, *str);
	if (flag)
		res[0] = (pf->plus) ? '+' : ' ';
	free(*str);
	return (res);
}

char	*float_zero_treatment(t_printf *pf, char **str)
{
	char	*res;
	int		flag;
	int		i;
	int		len;
	int		n;

	flag = (!(ft_isdigit(*str[0]))) ? 1 : 0;
	i = (!(ft_isdigit(*str[0]))) ? 1 : 0;
	len = ft_strlen(*str);
	n = (len < pf->width) ? pf->width : len;
	if (!(res = ft_memalloc(sizeof(char) * (n + 1))))
		exit(1);
	ft_memset(res, '0', n + 1);
	while (i < pf->width - len + flag)
		i++;
	ft_strcpy(res + i, *str + flag);
	if (flag)
	{
		res[0] = (pf->plus) ? '+' : ' ';
		res[0] = (*str[0] == '-') ? '-' : res[0];
	}
	free(*str);
	return (res);
}
