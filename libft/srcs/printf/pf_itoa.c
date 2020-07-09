/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:48:57 by fallard           #+#    #+#             */
/*   Updated: 2020/02/18 18:36:50 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_uint_size(uintmax_t n, int mod)
{
	int len;

	len = (mod < 0) ? 1 : 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_ulong_itoa(uintmax_t n, int mod)
{
	int		len;
	char	*arr;

	if (n == 0 && mod == 1)
		return (ft_strdup("0"));
	if (n == 0 && mod == -1)
		return (ft_strdup("-0"));
	len = get_uint_size(n, mod);
	if (!(arr = ft_memalloc(len + 1)))
		return (NULL);
	if (mod < 0)
		arr[0] = '-';
	while (n)
	{
		arr[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (arr);
}

int		without_zero(int *tab, int size)
{
	int i;

	i = size - 1;
	while (i >= 0 && tab[i] == 0)
		i--;
	return (i + 2);
}

char	*long_int_to_char_rev(int *tab, int size)
{
	char	*res;
	t_itoa	iter;
	int		len;
	int		i;

	len = without_zero(tab, size);
	if (!(res = ft_memalloc(sizeof(char) * (len * 4 + 1))))
		exit(1);
	iter.k = 0;
	i = len - 1;
	while (i >= 0)
	{
		iter.n = 1000;
		iter.j = 0;
		while (iter.j < 4)
		{
			res[iter.k++] = ((tab[i] / iter.n) % 10) + 48;
			iter.j++;
			iter.n = iter.n / 10;
		}
		i--;
	}
	res[iter.k] = '\0';
	return (res);
}

char	*long_int_to_char(int *tab, int size)
{
	char	*res;
	t_itoa	iter;
	int		len;
	int		i;

	len = without_zero(tab, size);
	if (!(res = ft_memalloc(sizeof(char) * (len * 4 + 1))))
		exit(1);
	iter.k = 0;
	i = 0;
	while (i <= len - 1)
	{
		iter.n = 1000;
		iter.j = 0;
		while (iter.j < 4)
		{
			res[iter.k++] = ((tab[i] / iter.n) % 10) + 48;
			iter.j++;
			iter.n = iter.n / 10;
		}
		i++;
	}
	res[iter.k] = '\0';
	return (res);
}
