/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 07:24:15 by fallard           #+#    #+#             */
/*   Updated: 2020/08/11 02:08:32 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_width_terminal(t_ls *ls)
{
	t_win	win;

	if (ioctl(1, TIOCGWINSZ, &win) < 0)
		ls->key_one = 1;
	ls->tty_width = win.ws_col;
	
}

int		main(int argc, char **argv)
{
	t_ls ls;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	get_width_terminal(&ls);
	parse_args_to_keys(&ls, argc, argv);
	parse_args_to_file(&ls, argc, argv);
	do_ls(&ls);
	return (0);
}
