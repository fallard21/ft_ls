/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_iso_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:24:46 by cgamora           #+#    #+#             */
/*   Updated: 2020/02/22 22:55:19 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_month(int ost, int flag)
{
	if (ost <= 2678400)
		return (1);
	if (ost <= 5097600 + (flag * 86400))
		return (2);
	if (ost <= 7776000 + (flag * 86400))
		return (3);
	if (ost <= 10368000 + (flag * 86400))
		return (4);
	if (ost <= 13046400 + (flag * 86400))
		return (5);
	if (ost <= 15638400 + (flag * 86400))
		return (6);
	if (ost <= 18316800 + (flag * 86400))
		return (7);
	if (ost <= 20995200 + (flag * 86400))
		return (8);
	if (ost <= 23587200 + (flag * 86400))
		return (9);
	if (ost <= 26265600 + (flag * 86400))
		return (10);
	if (ost <= 28857600 + (flag * 86400))
		return (11);
	if (ost <= 31536000 + (flag * 86400))
		return (12);
	return (0);
}

int			ft_day(int day, int flag)
{
	if (day <= 31)
		return (day);
	if (day <= 59 + flag)
		return (day - 31);
	if (day <= 90 + flag)
		return (day - (59 + flag));
	if (day <= 120 + flag)
		return (day - (90 + flag));
	if (day <= 151 + flag)
		return (day - (120 + flag));
	if (day <= 181 + flag)
		return (day - (151 + flag));
	if (day <= 212 + flag)
		return (day - (181 + flag));
	if (day <= 243 + flag)
		return (day - (212 + flag));
	if (day <= 273 + flag)
		return (day - (243 + flag));
	if (day <= 304 + flag)
		return (day - (273 + flag));
	if (day <= 334 + flag)
		return (day - (304 + flag));
	if (day <= 365 + flag)
		return (day - (334 + flag));
	return (0);
}

int			ft_dayen(int n, int i)
{
	int k;

	k = 1;
	k += n / 86400;
	return (ft_day(k, (i + 1970) % 4 == 0 ? 1 : 0));
}

char		*ft_date_print(int i, int n, char *str)
{
	str[0] = ((i + 1970) / 1000) + '0';
	str[1] = ((i + 1970) / 100) % 10 + '0';
	str[2] = ((i + 1970) / 10) % 10 + '0';
	str[3] = ((i + 1970) % 10) + '0';
	str[4] = '-';
	str[5] = (ft_month(n, (1970 + i) % 4 == 0 ? 1 : 0) / 10) + '0';
	str[6] = (ft_month(n, (1970 + i) % 4 == 0 ? 1 : 0) % 10) + '0';
	str[7] = '-';
	str[8] = ((ft_dayen(n, i)) / 10) + '0';
	str[9] = ((ft_dayen(n, i)) % 10) + '0';
	str[10] = 'T';
	n = n % 86400;
	str[11] = (n / 3600) / 10 + '0';
	str[12] = (n / 3600) % 10 + '0';
	str[13] = ':';
	n -= (n / 3600) * 3600;
	str[14] = (n / 60) / 10 + '0';
	str[15] = (n / 60) % 10 + '0';
	str[16] = ':';
	n -= (n / 60) * 60;
	str[17] = n / 10 + '0';
	str[18] = n % 10 + '0';
	str[19] = '\0';
	return (str);
}

char		*ft_date_printm(int i, int n, char *str)
{
	str[0] = ((i + 1901) / 1000) + '0';
	str[1] = ((i + 1901) / 100) % 10 + '0';
	str[2] = ((i + 1901) / 10) % 10 + '0';
	str[3] = ((i + 1901) % 10) + '0';
	str[4] = '-';
	str[5] = (ft_month(n, (1901 + i) % 4 == 0 ? 1 : 0) / 10) + '0';
	str[6] = (ft_month(n, (1901 + i) % 4 == 0 ? 1 : 0) % 10) + '0';
	str[7] = '-';
	str[8] = ((ft_dayen(n, i)) / 10) + '0';
	str[9] = ((ft_dayen(n, i)) % 10) + '0';
	str[10] = 'T';
	n = n % 86400;
	str[11] = (n / 3600) / 10 + '0';
	str[12] = (n / 3600) % 10 + '0';
	str[13] = ':';
	n -= (n / 3600) * 3600;
	str[14] = (n / 60) / 10 + '0';
	str[15] = (n / 60) % 10 + '0';
	str[16] = ':';
	n -= (n / 60) * 60;
	str[17] = n / 10 + '0';
	str[18] = n % 10 + '0';
	str[19] = '\0';
	return (str);
}
