/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:46:45 by tima              #+#    #+#             */
/*   Updated: 2020/06/22 16:54:43 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

void	ft_exit()
{
	perror("ls");
	exit(EXIT_FAILURE);
}

void	free_split(char ***str)
{
	int i;

	i = 0;
	if (*str == NULL)
		return ;
	while ((*str)[i])
	{
		ft_memdel((void**)&(*str)[i]);
		i++;
	}
	ft_memdel((void**)&(*str));
}
