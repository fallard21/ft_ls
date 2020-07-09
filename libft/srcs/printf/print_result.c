/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:19:22 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 01:23:39 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_o(t_printf *pf)
{
	char		*str;
	uintmax_t	n;
	int			len;
	int			hash;

	n = uspecifier(pf);
	hash = (pf->fhash && n != 0) ? 1 : 0;
	if (!(str = base8(n)))
		exit(1);
	len = (n == 0 && !pf->fhash && !pf->prec) ? 0 : ft_strlen(str);
	if (!pf->minus)
		print_width(hash, len, pf);
	ft_putnchar('0', pf->prec - len - hash);
	if (pf->prec < 0 && !pf->minus && pf->zero)
		ft_putnchar('0', pf->width - len - hash);
	if (pf->fhash && n != 0)
		ft_putchar('0');
	if (!(n == 0 && !pf->fhash && !pf->prec))
		ft_putstr(str);
	if (pf->minus)
		print_width(hash, len, pf);
	free(str);
	pf->tmp = (pf->width > (len + hash)) ? pf->width : len + hash;
	pf->len = pf->len + ((pf->tmp > pf->prec) ? pf->tmp : pf->prec);
}

void	print_u(t_printf *pf)
{
	char			*str;
	uintmax_t		n;
	int				len;

	n = uspecifier(pf);
	if (!(str = ft_ulong_itoa(n, 1)))
		exit(1);
	len = (n == 0 && !pf->prec) ? 0 : ft_strlen(str);
	if (!pf->minus)
		print_width(0, len, pf);
	if (pf->prec < 0 && !pf->minus && pf->zero)
		ft_putnchar('0', pf->width - len);
	ft_putnchar('0', pf->prec - len);
	if (!(n == 0 && !pf->prec))
		ft_putstr(str);
	if (pf->minus)
		print_width(0, len, pf);
	free(str);
	pf->tmp = (pf->width > len) ? pf->width : len;
	pf->len = pf->len + ((pf->tmp > pf->prec) ? pf->tmp : pf->prec);
}

void	print_x(t_printf *pf)
{
	char		*str;
	uintmax_t	n;
	int			len;
	int			hash;

	n = uspecifier(pf);
	hash = (pf->fhash && n != 0) ? 2 : 0;
	str = (pf->conv == 'x') ? base16(n, 0) : base16(n, 1);
	if (!str)
		exit(1);
	len = (n == 0 && !pf->prec) ? 0 : ft_strlen(str);
	if (!pf->minus)
		print_width(hash, len, pf);
	if (pf->fhash && n != 0)
		(pf->conv == 'x') ? (ft_putstr("0x")) : (ft_putstr("0X"));
	if (pf->prec < 0 && !pf->minus && pf->zero)
		ft_putnchar('0', pf->width - len - hash);
	ft_putnchar('0', pf->prec - len);
	if (!(n == 0 && !pf->prec))
		ft_putstr(str);
	if (pf->minus)
		print_width(hash, len, pf);
	free(str);
	pf->tmp = (pf->width > (len + hash)) ? pf->width : (len + hash);
	pf->len += ((pf->tmp > pf->prec + hash) ? pf->tmp : pf->prec + hash);
}

void	print_p(t_printf *pf)
{
	uintmax_t	n;
	char		*str;
	int			len;

	n = va_arg(pf->args, uintmax_t);
	if (!(str = base16(n, 0)))
		exit(1);
	len = (n == 0 && !pf->prec) ? 2 : ft_strlen(str) + 2;
	if (!pf->minus)
		print_width(0, len, pf);
	ft_putstr("0x");
	if (!(n == 0 && !pf->prec))
		ft_putstr(str);
	if (pf->minus)
		print_width(0, len, pf);
	free(str);
	pf->len = pf->len + ((pf->width > len) ? pf->width : len);
}

void	print_percent(t_printf *pf)
{
	if (!pf->minus)
		print_width(0, 1, pf);
	if (pf->zero && !pf->minus)
		ft_putnchar('0', pf->width - 1);
	write(1, "%%", 1);
	if (pf->minus)
		ft_putnchar(' ', pf->width - 1);
	pf->len = pf->len + ((pf->width > 1) ? pf->width : 1);
}
