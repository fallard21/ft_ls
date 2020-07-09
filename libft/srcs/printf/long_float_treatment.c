/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_float_treatment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:19:11 by fallard           #+#    #+#             */
/*   Updated: 2020/02/20 19:19:13 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parts_join(t_ldbl_cast dbl, t_floats *flt, t_printf *pf)
{
	char	*res;

	flt->one = long_int_to_char_rev(flt->first, flt->len_s);
	flt->two = long_int_to_char(flt->end, flt->len_e);
	flt->len_s = ft_strlen(flt->one);
	flt->len_e = ft_strlen(flt->two);
	if (plus_five(pf, flt))
		plus_one(flt);
	if (dbl.t_parts.sign)
		is_sign(flt);
	if (!(res = cut_precision(pf, flt)))
		exit(1);
	if (!(res = treatment_parts(pf, flt, res)))
		exit(1);
	return (res);
}

char	*treatment_parts(t_printf *pf, t_floats *flt, char *str)
{
	char	*res;
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (str[i] != '.')
		i++;
	if (pf->prec == 0 && !pf->fhash)
		res = ft_strsub(str, 0, i);
	else if (pf->prec > flt->len_e)
	{
		if (!(tmp = ft_memalloc(sizeof(char) * (pf->prec - flt->len_e + 1))))
			exit(1);
		ft_memset(tmp, '0', pf->prec - flt->len_e);
		if (!(res = ft_strjoin(str, tmp)))
			exit(1);
	}
	else
		res = ft_strdup(str);
	ft_memdel((void**)&str);
	ft_memdel((void**)&tmp);
	return (res);
}

void	is_sign(t_floats *flt)
{
	int i;

	i = 0;
	while (flt->one[i])
	{
		if (flt->one[i + 1] == '\0')
		{
			flt->one[i - 1] = '-';
			break ;
		}
		if (flt->one[i + 1] != '0')
		{
			flt->one[i] = '-';
			break ;
		}
		i++;
	}
}

char	*cut_precision(t_printf *pf, t_floats *flt)
{
	char	*bdot;
	char	*adot;
	char	*res;
	int		i;
	int		n;

	i = 0;
	n = (pf->prec < flt->len_e) ? pf->prec : flt->len_e;
	while (flt->one[i] && flt->one[i] == '0')
	{
		if (flt->one[i + 1] == '\0')
			break ;
		i++;
	}
	if (!(bdot = ft_strsub(flt->one, i, flt->len_s - i)))
		exit(1);
	if (!(adot = ft_strsub(flt->two, 0, n)))
		exit(1);
	if (!(res = ft_str_dot_join(bdot, adot)))
		exit(1);
	free(bdot);
	free(adot);
	return (res);
}

char	*ft_str_dot_join(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*res;
	int		len;

	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len = len1 + len2;
	if (!(res = ft_memalloc(sizeof(char) * (len + 2))))
		return (NULL);
	ft_strcpy(res, str1);
	res[len1] = '.';
	ft_strcpy(res + len1 + 1, str2);
	return (res);
}
