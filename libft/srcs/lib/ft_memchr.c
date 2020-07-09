/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:15:53 by fallard           #+#    #+#             */
/*   Updated: 2019/09/16 18:49:40 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i = i + 1;
	}
	return (NULL);
}
