/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:17:38 by fallard           #+#    #+#             */
/*   Updated: 2019/09/16 21:11:20 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	if (str2[j] == 0)
		return ((char*)&str1[i]);
	while (str1[i++])
	{
		while (str1[len] == str2[j] && str2[j] != '\0')
		{
			len++;
			j++;
		}
		if (str2[j] != '\0')
		{
			j = 0;
			len = i;
		}
		else
			return ((char*)&str1[len] - j);
	}
	return (NULL);
}
