/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:35:41 by fallard           #+#    #+#             */
/*   Updated: 2020/02/19 21:24:09 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf	*pf;
	int			len;

	if (!(pf = ft_memalloc(sizeof(t_printf))))
		return (-1);
	pf->format = (char*)format;
	pf->len = 0;
	va_start(pf->args, format);
	parse_format(pf);
	va_end(pf->args);
	len = pf->len;
	free(pf);
	return (len);
}

void	ft_color(t_printf *pf, int a)
{
	char	c;

	c = a + '0';
	if (pf->format[pf->i + 2] == '}')
	{
		write(1, "{", 1);
		write(1, &c, 1);
	}
	else
	{
		if (a == 1)
			write(1, "\x1b[31m", 5);
		if (a == 2)
			write(1, "\x1b[32m", 5);
		if (a == 3)
			write(1, "\x1b[33m", 5);
		if (a == 4)
			write(1, "\x1b[34m", 5);
		if (a == 5)
			write(1, "\x1b[35m", 5);
		if (a == 6)
			write(1, "\x1b[36m", 5);
		if (a == 0)
			write(1, "\x1b[0m", 4);
	}
}
