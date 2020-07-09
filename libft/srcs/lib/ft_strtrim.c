/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:09:32 by fallard           #+#    #+#             */
/*   Updated: 2019/09/13 20:09:13 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*fresh;

	if (s == 0)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	i = ft_strlen(s) - 1;
	end = i;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	if (s[start] == '\0')
		return (ft_strnew(1));
	if (start == 0 && end == i)
		fresh = ft_strdup(s);
	else
		fresh = ft_strsub(s, start, i - start + 1);
	return (fresh);
}
