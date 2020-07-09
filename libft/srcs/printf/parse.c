/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:18:47 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 23:23:36 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_format(t_printf *pf)
{
	pf->i = 0;
	while (pf->format[pf->i])
	{
		if (pf->format[pf->i] == '{' && pf->format[pf->i + 2] == '}')
		{
			pf->i++;
			ft_color(pf, (pf->format[pf->i]) - '0');
			pf->i = pf->i + 2;
			continue ;
		}
		if (pf->format[pf->i] == '%')
		{
			pf_init(pf);
			parse_flags(pf);
			print_result(pf);
		}
		else
		{
			write(1, &pf->format[pf->i], 1);
			pf->len++;
		}
		pf->i++;
	}
	return (0);
}

int		parse_flags(t_printf *pf)
{
	if (!(pf->conv = convchr(&pf->format[pf->i])))
		return (0);
	pf->i = pf->i + 1;
	while (pf->format[pf->i] != pf->conv)
	{
		pf->zero = (pf->format[pf->i] == '0' && pf->width == 0) ? 1 : pf->zero;
		pf->minus = (pf->format[pf->i] == '-') ? 1 : pf->minus;
		pf->plus = (pf->format[pf->i] == '+') ? 1 : pf->plus;
		pf->fhash = (pf->format[pf->i] == '#') ? 1 : pf->fhash;
		pf->space = (pf->format[pf->i] == ' ') ? 1 : pf->space;
		pf->wstar = (pf->format[pf->i] == '*') ? 1 : pf->wstar;
		if (pf->wstar == 1)
			parse_width(pf);
		if ('0' <= pf->format[pf->i] && pf->format[pf->i] <= '9' && !pf->wstar)
			pf->width = 10 * pf->width + pf->format[pf->i] - 48;
		if (pf->format[pf->i] == '.')
			parse_prec(pf, &pf->format[pf->i]);
		pf->spec = (pf->format[pf->i] == 'l') ? pf->spec + 'l' : pf->spec;
		pf->spec = (pf->format[pf->i] == 'h') ? pf->spec + 'h' : pf->spec;
		pf->spec = (pf->format[pf->i] == 'L') ? 'L' : pf->spec;
		pf->i++;
	}
	pf->width = (pf->width < 0) ? 0 : pf->width;
	return (0);
}

void	pf_init(t_printf *pf)
{
	pf->zero = 0;
	pf->minus = 0;
	pf->plus = 0;
	pf->fhash = 0;
	pf->space = 0;
	pf->width = 0;
	pf->prec = -1;
	pf->wstar = 0;
	pf->conv = 0;
	pf->spec = 0;
}

int		convchr(char *str)
{
	char	*conv;
	int		i;
	int		j;

	conv = "diouxXcspfFbk";
	i = 1;
	while (str[i])
	{
		j = 0;
		while (conv[j])
		{
			if (str[i] == 37)
				return (37);
			if (str[i] == conv[j])
				return (conv[j]);
			j++;
		}
		i++;
	}
	return (0);
}
