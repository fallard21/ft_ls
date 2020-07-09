/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:19:30 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:19:32 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	specifier(t_printf *pf)
{
	intmax_t res;

	if (pf->spec == 104)
		res = (short)va_arg(pf->args, int);
	else if (pf->spec == 208)
		res = (char)va_arg(pf->args, int);
	else if (pf->spec == 108)
		res = (long)va_arg(pf->args, long);
	else if (pf->spec == 216)
		res = (long long)va_arg(pf->args, long long);
	else
		res = (int)va_arg(pf->args, int);
	return (res);
}

uintmax_t	uspecifier(t_printf *pf)
{
	uintmax_t res;

	if (pf->spec == 104)
		res = (unsigned short)va_arg(pf->args, unsigned int);
	else if (pf->spec == 208)
		res = (unsigned char)va_arg(pf->args, unsigned int);
	else if (pf->spec == 108)
		res = (unsigned long)va_arg(pf->args, unsigned long);
	else if (pf->spec == 216)
		res = (unsigned long long)va_arg(pf->args, unsigned long long);
	else
		res = (unsigned int)va_arg(pf->args, unsigned int);
	return (res);
}
