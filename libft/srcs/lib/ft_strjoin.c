/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:46:23 by fallard           #+#    #+#             */
/*   Updated: 2020/06/16 13:22:10 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(res = ft_memalloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	return (res);
}
