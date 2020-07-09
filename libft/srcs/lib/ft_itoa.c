/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:45:52 by fallard           #+#    #+#             */
/*   Updated: 2020/06/19 21:36:10 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_arr(int len)
{
	int i;

	i = 0;
	if (len <= 0)
	{
		len = len * (-1);
		i = i + 1;
	}
	while (len)
	{
		len = len / 10;
		i = i + 1;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*arr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = size_arr(n);
	if (!(arr = ft_memalloc(i + 1)))
		return (NULL);
	if (n == 0)
		ft_memset(arr, '0', 1);
	if (n < 0)
	{
		n = n * -1;
		arr[0] = '-';
	}
	while (n)
	{
		arr[i - 1] = n % 10 + 48;
		n = n / 10;
		i = i - 1;
	}
	return (arr);
}
