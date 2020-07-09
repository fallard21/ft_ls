/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_iso_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:09:34 by cgamora           #+#    #+#             */
/*   Updated: 2020/02/23 00:17:06 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_date(int n, char *str)
{
	int i;
	int c;

	c = 0;
	if (n < 0)
	{
		n += 2147483648;
		if (n < 0)
			n *= -1;
		i = n / 31436000;
		c = (i + 1) / 4;
		n += 29969152;
		n -= (i * 31536000) + (c * 86400);
		return (ft_date_printm(i, n, str));
	}
	i = n / 31436000;
	c = (i + 1) / 4;
	n -= (i * 31536000) + (c * 86400);
	return (ft_date_print(i, n, str));
}

void		print_k(t_printf *pf)
{
	int		n;
	char	*str;

	n = va_arg(pf->args, int);
	if (!(str = ft_memalloc(sizeof(char) * 20)))
		exit(1);
	ft_date(n, str);
	if (!pf->minus)
		print_width(0, 19, pf);
	ft_putstr(str);
	if (pf->minus)
		print_width(0, 19, pf);
	free(str);
	pf->len = pf->len + ((pf->width > 19) ? pf->width : 19);
}
