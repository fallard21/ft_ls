/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:46:23 by fallard           #+#    #+#             */
/*   Updated: 2020/06/16 13:22:44 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *str, char *del)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!str || !del)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(del) + 1;
	if (!(res = ft_memalloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	i = 0;
	while (del[i])
		res[j++] = del[i++];
	free(del);
	return (res);
}
