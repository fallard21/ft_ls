/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:49:15 by fallard           #+#    #+#             */
/*   Updated: 2020/06/19 21:32:35 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)s;
	if (!n || dest == s)
		return (dest);
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
