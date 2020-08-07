/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 23:42:41 by tima              #+#    #+#             */
/*   Updated: 2020/08/07 03:32:00 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		free_list(t_file **head)
{
	t_file *next;

	while (*head)
	{
		next = (*head)->next;
		ft_strdel(&(*head)->name);
		ft_strdel(&(*head)->gid_name);
		ft_strdel(&(*head)->uid_name);
		free(*head);
		*head = next;
	}
	*head = NULL;
	return (1);
}

void	ft_exit()
{
	perror("ls");
	exit(EXIT_FAILURE);
}

int		free_split(char ***str)
{
	int i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			ft_memdel((void**)&(*str)[i]);
			i++;
		}
	}
	ft_memdel((void**)&(*str));
	return (1);
}

int		free_data(t_data data)
{
	free_list(&data.head);
	ft_memdel((void**)&data.width);
	return (1);
}