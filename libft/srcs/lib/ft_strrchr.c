/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:37:33 by fallard           #+#    #+#             */
/*   Updated: 2019/09/19 17:38:40 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if (str[i] == c)
		return ((char*)&str[i]);
	while (str[i] != c && i > 0)
	{
		if (str[i - 1] == c)
			return ((char*)&str[i - 1]);
		i = i - 1;
	}
	return (NULL);
}
