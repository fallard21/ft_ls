/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:59:30 by fallard           #+#    #+#             */
/*   Updated: 2019/09/12 18:09:36 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (size <= dstlen)
		return (srclen + size);
	while (dst[i] != '\0' && i < size - 1)
		i = i + 1;
	while (*src && i < size - 1)
	{
		dst[i] = *src;
		i = i + 1;
		src++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}
