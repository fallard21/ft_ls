/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:01:16 by fallard           #+#    #+#             */
/*   Updated: 2019/11/28 16:00:05 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		negative;
	int		res;

	i = 0;
	negative = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i = i + 1;
	if (str[i] == '-')
		negative = 1;
	if (str[i] == '-' || str[i] == '+')
		i = i + 1;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i = i + 1;
	}
	if (negative == 1)
		return (-res);
	else
		return (res);
}
