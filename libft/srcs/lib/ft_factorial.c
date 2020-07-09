/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:53:50 by fallard           #+#    #+#             */
/*   Updated: 2020/05/29 01:57:56 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_llfactorial(long long nb)
{
	if (nb < 0 || nb > 25)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	else
		return (nb * ft_llfactorial(nb - 1));
}
