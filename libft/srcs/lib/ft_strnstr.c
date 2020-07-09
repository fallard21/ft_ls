/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:48:45 by fallard           #+#    #+#             */
/*   Updated: 2019/09/20 15:10:26 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	n;

	if (*str2 == '\0')
		return ((char *)str1);
	n = ft_strlen(str2);
	while (*str1 != '\0' && len >= n)
	{
		if (*str1 == *str2 && ft_strncmp(str1, str2, n) == 0)
			return ((char *)str1);
		str1++;
		len--;
	}
	return (NULL);
}
