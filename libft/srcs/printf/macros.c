/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:57:22 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 00:35:56 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			dec_mod(intmax_t n)
{
	return ((n < 0) ? -1 : 1);
}

int			pf_zero(int n)
{
	return ((n < 0) ? 0 : n);
}

intmax_t	dec_abs(intmax_t n)
{
	return ((n < 0) ? -n : n);
}

t_double_l	pf_abs(t_double_l n)
{
	return ((n < 0) ? -n : n);
}
