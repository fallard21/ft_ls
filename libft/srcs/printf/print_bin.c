/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:21:38 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:21:40 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_b(t_printf *pf)
{
	uintmax_t	n;
	char		*res;
	int			len;
	int			hash;

	n = va_arg(pf->args, uintmax_t);
	hash = (pf->fhash && n != 0) ? 2 : 0;
	if (!(res = base2(n)))
		exit(1);
	if (pf->space)
		res = treatment_bin(res);
	len = (n == 0 && !pf->prec) ? 0 : ft_strlen(res);
	if (!pf->minus)
		print_width(hash, len, pf);
	(pf->fhash && n != 0) ? ft_putstr("0b") : ft_putstr("");
	if (pf->prec < 0 && !pf->minus && pf->zero)
		ft_putnchar('0', pf->width - len - hash);
	ft_putnchar('0', pf->prec - len);
	if (!(n == 0 && !pf->prec))
		ft_putstr(res);
	if (pf->minus)
		print_width(hash, len, pf);
	free(res);
	pf->tmp = (pf->width > (len + hash)) ? pf->width : (len + hash);
	pf->len += ((pf->tmp > pf->prec + hash) ? pf->tmp : pf->prec + hash);
}

char	*treatment_bin(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*res;
	t_bin	bin;

	bin.s = get_num_space(str);
	bin.max_len = ft_strlen(str) + bin.s + 1;
	if (!(res = ft_memalloc(sizeof(char) * bin.max_len)))
		exit(1);
	i = bin.max_len - 2;
	j = ft_strlen(str) - 1;
	k = 1;
	while (i >= 0 && j >= 0)
	{
		res[i--] = str[j--];
		if (k % 4 == 0 && bin.s-- > 0)
			res[i--] = ' ';
		k++;
	}
	free(str);
	return (res);
}

int		get_num_space(char *str)
{
	int	i;
	int	len;
	int	count;

	len = ft_strlen(str);
	i = len;
	count = 0;
	while (i > 4)
	{
		i = i - 4;
		count++;
	}
	return (count);
}
