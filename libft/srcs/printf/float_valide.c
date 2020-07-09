/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_valide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:00:40 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 00:28:32 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		error_f(t_printf *pf, t_ldbl_cast dbl)
{
	int		err;
	char	*str;
	int		len;

	err = valide_float(dbl);
	str = (err == 1 && err != 3) ? ft_strdup("inf") : ft_strdup("-inf");
	str = (err == 3) ? ft_strdup("nan") : str;
	if (!str)
		exit(1);
	len = ft_strlen(str);
	if (pf->plus && ft_strcmp(str, "inf") == 0)
		len++;
	if (!pf->minus)
		print_width(pf->plus, len, pf);
	if (pf->plus && ft_strcmp(str, "inf") == 0)
		ft_putchar('+');
	ft_putstr(str);
	if (pf->minus)
		print_width(pf->plus, len, pf);
	free(str);
	pf->tmp = (pf->width > len) ? pf->width : len;
	pf->len = pf->len + pf->tmp;
}

int			valide_float(t_ldbl_cast dbl)
{
	if (dbl.t_parts.exponent == 32767u &&
			dbl.t_parts.mantissa == 9223372036854775808ul &&
			dbl.t_parts.sign == 0u)
		return (1);
	if (dbl.t_parts.exponent == 32767u &&
			dbl.t_parts.mantissa == 9223372036854775808ul &&
			dbl.t_parts.sign == 1u)
		return (2);
	if (dbl.t_parts.exponent == 32767u &&
			dbl.d != dbl.d)
		return (3);
	return (0);
}

t_floats	*create_struct(void)
{
	t_floats	*res;

	if (!(res = ft_memalloc(sizeof(t_floats))))
		return (NULL);
	return (res);
}

void		pf_free_floats(t_floats *flt)
{
	ft_memdel((void **)&flt->first);
	ft_memdel((void **)&flt->end);
	ft_memdel((void **)&flt->mant);
	ft_memdel((void **)&flt->one);
	ft_memdel((void **)&flt->two);
	ft_memdel((void **)&flt);
}
