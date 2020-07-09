/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:18:50 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 17:54:32 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(int hash, int len, t_printf *pf)
{
	int n;
	int prec;

	if (pf->conv == 'o')
		prec = pf->prec - len - hash;
	else
		prec = pf->prec - len;
	n = pf->width - hash - pf_zero(prec) - len;
	if (pf->zero && pf->prec < 0 && !pf->minus)
		n = 0;
	if (pf->conv == 's')
		n = pf->width - len;
	if (pf->conv == 'd')
		n = pf->width - len - hash;
	if ((pf->conv == 'f' || pf->conv == 'F') && pf->zero && !pf->minus)
		n = 0;
	if (n > 0)
		ft_putnchar(' ', n);
}

void	ft_putnchar(char c, long count)
{
	char	*str;

	if (count <= 0)
		return ;
	str = ft_memalloc(sizeof(char) * (count + 1));
	if (!str)
		exit(1);
	ft_memset(str, c, count);
	write(1, str, count);
	free(str);
}

void	parse_width(t_printf *pf)
{
	pf->width = va_arg(pf->args, int);
	if (pf->width < 0)
		pf->minus = 1;
	pf->width = pf_abs(pf->width);
	pf->wstar = 2;
}

void	parse_prec(t_printf *pf, char *str)
{
	int i;

	pf->prec = 0;
	i = 1;
	if (str[i] == '*')
	{
		pf->prec = va_arg(pf->args, int);
		if (pf->prec < 0)
			pf->prec = -1;
		i++;
	}
	else
	{
		while ('0' <= str[i] && str[i] <= '9')
		{
			pf->prec = 10 * pf->prec + str[i] - 48;
			if (pf->prec < 0)
			{
				pf->prec = -1;
				break ;
			}
			i++;
		}
	}
	pf->i = pf->i + (i - 1);
}
