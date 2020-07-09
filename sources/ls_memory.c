/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 23:42:41 by tima              #+#    #+#             */
/*   Updated: 2020/07/08 00:20:21 by tima             ###   ########.fr       */
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
