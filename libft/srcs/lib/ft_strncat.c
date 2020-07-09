/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:42:16 by fallard           #+#    #+#             */
/*   Updated: 2019/09/10 16:53:27 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str1, const char *str2, size_t n)
{
	size_t	i;
	int		len;

	len = ft_strlen(str1);
	i = 0;
	while (str2[i] != '\0' && i < n)
	{
		str1[len + i] = str2[i];
		i = i + 1;
	}
	str1[i + len] = '\0';
	return (str1);
}
