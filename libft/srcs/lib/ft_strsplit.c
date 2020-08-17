/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:20:18 by fallard           #+#    #+#             */
/*   Updated: 2020/07/06 20:17:49 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	if (len == 0)
		return (0);
	if (str[i] != c)
		j = j + 1;
	while (str[i] && i < (len - 1))
	{
		if (str[i] == c && str[i + 1] != c)
			j = j + 1;
		i = i + 1;
	}
	return (j);
}

static int		word_len(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i = i + 1;
	while (s[i] != c && s[i])
	{
		i = i + 1;
		len = len + 1;
	}
	return (len);
}

static char		**split_error(char **fresh, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(fresh[i]);
		i = i + 1;
	}
	free(fresh);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	k = 0;
	if (!s || !(arr = ft_memalloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	len = count_words(s, c);
	while (i < len)
	{
		j = 0;
		if (!(arr[i] = ft_strnew(word_len(&s[k], c))))
			return (split_error(arr, i));
		while (s[k] == c)
			k = k + 1;
		while (s[k] != c && s[k])
			arr[i][j++] = s[k++];
		i++;
	}
	return (arr);
}
