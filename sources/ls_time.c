/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:59:57 by tima              #+#    #+#             */
/*   Updated: 2020/07/15 05:59:51 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_time(time_t time)
{
	char	**str;
	int i = 1;

	str = ft_strsplit(ctime(&time), ' ');
	
	while (i < 4)
	{
		ft_printf("%2.5s ", str[i]);
		i++;
	}
	free_split(&str);
}
