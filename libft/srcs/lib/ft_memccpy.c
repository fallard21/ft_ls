/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:15:45 by fallard           #+#    #+#             */
/*   Updated: 2019/09/11 19:49:01 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char*)dest;
	s2 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == (unsigned char)c)
			return (&s1[i] + 1);
		i = i + 1;
	}
	return (NULL);
}
