/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:14:32 by fallard           #+#    #+#             */
/*   Updated: 2019/09/13 17:44:27 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*fresh;

	if (s == NULL)
		return (NULL);
	fresh = malloc(sizeof(*fresh) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < len)
	{
		fresh[i] = s[start + i];
		i = i + 1;
	}
	fresh[i] = '\0';
	return (fresh);
}
