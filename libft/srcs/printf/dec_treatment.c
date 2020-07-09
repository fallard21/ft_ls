/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:20:23 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 00:13:28 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero_negative_flag(t_printf *pf, char **str)
{
	int		i;
	char	*tmp;
	int		len;
	int		n;

	i = 1;
	len = ft_strlen(*str);
	n = (pf->width < len) ? len : pf->width;
	if (!(tmp = ft_memalloc(sizeof(char) * (n + 1))))
		exit(1);
	ft_memset(tmp, '0', n + 1);
	while (i < (pf->width - len) + 1)
		i++;
	ft_strcpy(tmp + i, *str + 1);
	tmp[0] = '-';
	free(*str);
	return (tmp);
}

char	*zero_positive_flag(t_printf *pf, char **str)
{
	int		i;
	int		flag;
	char	*tmp;
	int		len;
	int		n;

	len = ft_strlen(*str);
	flag = (*str[0] == '+' || *str[0] == ' ') ? 1 : 0;
	i = (flag) ? 1 : 0;
	n = (pf->width < len) ? len : pf->width;
	if (!(tmp = ft_memalloc(sizeof(char) * (n + 1))))
		exit(1);
	ft_memset(tmp, '0', n + 1);
	while (i < (pf->width - len) + flag)
		i++;
	ft_strcpy(tmp + i, *str + flag);
	if (flag)
		tmp[0] = (pf->plus) ? '+' : ' ';
	free(*str);
	return (tmp);
}

char	*flag_neg_prec(t_printf *pf, char **str)
{
	char	*res;
	int		len;
	int		i;
	int		n;

	len = ft_strlen(*str) - 1;
	i = 1;
	n = len + 1 + pf_zero(pf->prec - len);
	if (!(res = ft_memalloc(sizeof(char) * (n + 1))))
		exit(1);
	ft_memset(res, '0', n + 1);
	res[0] = '-';
	while (i < (pf->prec - len) + 1)
		i++;
	ft_strcpy(res + i, *str + 1);
	free(*str);
	return (res);
}

char	*flag_pos_prec(t_printf *pf, char **str)
{
	char	*res;
	int		len;
	int		i;
	int		flag;
	int		n;

	i = 0;
	flag = 0;
	len = ft_strlen(*str);
	if (pf->space || pf->plus)
	{
		flag = 1;
		i = 1;
	}
	n = len + flag + pf_zero(pf->prec - len);
	if (!(res = ft_memalloc(sizeof(char) * (n + 1))))
		exit(1);
	ft_memset(res, '0', n + 1);
	while (i < (pf->prec - len) + flag)
		i++;
	ft_strcpy(res + i, *str);
	if (flag)
		res[0] = (pf->plus) ? '+' : ' ';
	free(*str);
	return (res);
}
