/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_chmod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 22:19:10 by tima              #+#    #+#             */
/*   Updated: 2020/07/08 00:26:08 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_chmod(mode_t mode)
{
	int		chmod[3];
	mode_t	tmp;
	char	*res;
	int		i;

	tmp = mode;
	i = 0;
	if (!(res = ft_calloc(11, sizeof(char))))
		ft_exit();
	ft_memset(chmod, 0, sizeof(int) * 3);
	while (i < 3)
	{
		chmod[i++] = tmp % 8;
		tmp = tmp / 8;
	}
	init_chmod(res, chmod, mode);
	ft_printf("{3}%s{0} \n", res);
	free(res);
}

void	init_chmod(char *res, int chmod[3], mode_t mode)
{
	res[0] = get_type(mode);

	res[1] = (chmod[2] > 3) ? 'r' : '-';
	res[2] = (chmod[2] > 1 && chmod[2] != 4 && chmod[2] != 5) ? 'w' : '-';
	res[3] = (chmod[2] & 1) ? 'x' : '-';

	res[4] = (chmod[1] > 3) ? 'r' : '-';
	res[5] = (chmod[1] > 1 && chmod[1] != 4 && chmod[1] != 5) ? 'w' : '-';
	res[6] = (chmod[1] & 1) ? 'x' : '-';

	res[7] = (chmod[0] > 3) ? 'r' : '-';
	res[8] = (chmod[0] > 1 && chmod[0] != 4 && chmod[0] != 5) ? 'w' : '-';
	res[9] = (chmod[0] & 1) ? 'x' : '-';
}

char	get_type(mode_t mode)
{
	char s;

	if (S_ISDIR(mode))
		s = 'd';
	else if (S_ISLNK(mode))
		s = 'l';
	else
		s = '-';
	return (s);
}
