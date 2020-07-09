/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:01:14 by fallard           #+#    #+#             */
/*   Updated: 2019/09/11 19:16:04 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)dest;
	i = 0;
	if (n == 0)
		return (str);
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i = i + 1;
	}
	return (str);
}
