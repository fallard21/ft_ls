/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:40:06 by fallard           #+#    #+#             */
/*   Updated: 2019/09/10 16:40:20 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *str1, const char *str2)
{
	int i;
	int len;

	len = ft_strlen(str1);
	i = 0;
	while (str2[i] != '\0')
	{
		str1[i + len] = str2[i];
		i = i + 1;
	}
	str1[i + len] = '\0';
	return (str1);
}
