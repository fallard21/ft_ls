/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 07:24:15 by fallard           #+#    #+#             */
/*   Updated: 2020/07/23 07:24:17 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
void	sort_words(char **word, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while(i < (size - 1))
	{
		j = 0;
		while (j < (size - 1 - i))
		{
			if (ft_strcmp(word[j], word[j + 1]) > 0)
			{
				tmp = word[j];
				word[j] = word[j + 1];
				word[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
*/

int		ls_without_args(t_ls *ls)
{	
	if (!(ls->args = get_dir_files(ls, "./")))
		return (1);
	ls->args = sort_list(cmp_name, ls->args);
	
	calculate_column(ls, ls->args);
	free_list(&ls->args);
	return (0);
}

void	get_width_terminal(t_ls *ls)
{
	t_win	win;

	//ft_printf("status: %d\n", isatty(1));
	if ((ioctl(1, TIOCGWINSZ, &win)) < 0)
	{
		perror("ioctl");
		exit (EXIT_FAILURE);
	}
	ls->tty_width = win.ws_col;
	//ls->tty_row = win.ws_row;
	//ft_printf("tty_width(x): %d\n", ls->tty_width);
}

int	main(int argc, char **argv)
{
	t_ls ls;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	get_width_terminal(&ls);
	if (argc == 1)
		ls_without_args(&ls);
	else
	{	
		parse_keys_args(&ls, argc, argv);
		parse_file_args(&ls, argc, argv);
		//print_list(ls.args);
		choosing_ls(&ls);
		//ft_printf("{1}flag_args: %d{0}\n", ls.flag_args);
		//ft_printf("{1}flag_keys: %d{0}\n", ls.flag_keys);
	}
	return (0);
}
