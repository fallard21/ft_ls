/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 23:42:41 by tima              #+#    #+#             */
/*   Updated: 2020/07/20 09:53:39 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_list(t_file **head)
{
	t_file *next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->name);
		free((*head)->gid_name);
		free((*head)->uid_name);
		free(*head);
		*head = next;
	}
	*head = NULL;
}

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
