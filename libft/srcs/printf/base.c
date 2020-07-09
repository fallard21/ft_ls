/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:07:03 by fallard           #+#    #+#             */
/*   Updated: 2020/02/17 19:13:52 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*base2(uintmax_t n)
{
	char	*res;
	int		i;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = get_base_size(n, 2);
	if (!(res = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = len - 1;
	while (n)
	{
		res[i] = n % 2 + 48;
		n = n / 2;
		i--;
	}
	return (res);
}

char	*base8(uintmax_t n)
{
	char	*res;
	int		i;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = get_base_size(n, 8);
	if (!(res = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(res, 0, len + 1);
	i = len - 1;
	while (n)
	{
		res[i] = n % 8 + 48;
		n = n / 8;
		i--;
	}
	return (res);
}

char	*base16(uintmax_t n, int c)
{
	char	*hex;
	char	*res;
	int		i;
	int		len;

	if (c == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	len = get_base_size(n, 16);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(res = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(res, 0, len + 1);
	i = len - 1;
	while (n)
	{
		res[i] = hex[n % 16];
		n = n / 16;
		i--;
	}
	return (res);
}

int		get_base_size(uintmax_t n, int base)
{
	int i;

	i = 0;
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}
