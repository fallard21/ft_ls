/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 07:24:15 by fallard           #+#    #+#             */
/*   Updated: 2020/07/27 19:47:15 by fallard          ###   ########.fr       */
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

/*
int		ls_without_args(t_ls *ls)
{	
	if (!(ls->args = get_dir_files(ls, "./")))
		return (1);
	ls->args = sort_list(cmp_name, ls->args);
	
	print_column(ls, ls->args);
	free_list(&ls->args);
	return (0);
}
*/

void	get_width_terminal(t_ls *ls)
{
	t_win  win;

	if (isatty(1))
	{
		ioctl(1, TIOCGWINSZ, &win);
		ls->tty_width = win.ws_col;
		ls->tty_flag = 1;
	}
	//ft_printf("%d, %d\n", ls->tty_flag, ls->tty_width);
}

int	main(int argc, char **argv)
{
	t_ls ls;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	get_width_terminal(&ls);
	
	parse_args_to_keys(&ls, argc, argv);
	if (parse_args_to_file(&ls, argc, argv))
		return (EXIT_FAILURE);
	//print_list(ls.args);
	choosing_ls(&ls);
	//ft_printf("{1}flag_args: %d{0}\n", ls.flag_args);
	//ft_printf("{1}flag_keys: %d{0}\n", ls.flag_keys);
	return (0);
}
