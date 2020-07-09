/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:35:57 by fallard           #+#    #+#             */
/*   Updated: 2020/06/11 09:48:53 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <float.h>

# define INTEGER_PART 1300
# define FRACTION_MAX 4150
# define FRACTION_MIN 200

typedef long double	t_double_l;

typedef struct	s_printf
{
	char		*format;
	int			zero;
	int			minus;
	int			plus;
	int			fhash;
	int			space;
	int			width;
	int			prec;
	int			wstar;
	int			conv;
	int			spec;
	int			len;
	int			tmp;
	int			i;
	va_list		args;
}				t_printf;

typedef union	u_ldbl_cast
{
	t_double_l	d;
	struct		s_parts
	{
		uintmax_t		mantissa : 64;
		unsigned int	exponent : 15;
		unsigned int	sign : 1;
	}			t_parts;
}				t_ldbl_cast;

typedef struct	s_floats
{
	int			*first;
	int			*end;
	char		*mant;
	int			mant_len;
	int			len_s;
	int			len_e;
	char		*one;
	char		*two;
}				t_floats;

typedef struct	s_bin
{
	int			n;
	int			s;
	int			max_len;

}				t_bin;

typedef struct	s_itoa
{
	int			j;
	int			k;
	int			n;
}				t_itoa;

/*
** >>----------------------------- MAIN FUNCTION -----------------------------<<
*/
int				ft_printf(const char *format, ...);

/*
** >>--------------------------------- PARSE ---------------------------------<<
*/
int				parse_format(t_printf *pf);
int				parse_flags(t_printf *pf);
void			pf_init(t_printf *pf);
void			parse_prec(t_printf *pf, char *str);
int				convchr(char *str);
void			parse_width(t_printf *pf);

/*
** >>------------------------------ PRINT FLAGS ------------------------------<<
*/
void			print_result(t_printf *pf);
void			print_d(t_printf *pf);
void			print_o(t_printf *pf);
void			print_u(t_printf *pf);
void			print_x(t_printf *pf);
void			print_c(t_printf *pf);
void			print_s(t_printf *pf);
void			print_p(t_printf *pf);
void			print_f(t_printf *pf);
void			print_percent(t_printf *pf);

/*
** >>------------------------------- SPECIFIER -------------------------------<<
*/
uintmax_t		uspecifier(t_printf *pf);
intmax_t		specifier(t_printf *pf);

/*
** >>-------------------------------- DECIMAL --------------------------------<<
*/
void			put_pozitive_d(t_printf *pf, char **str);
void			put_negative_d(t_printf *pf, char **str);
void			put_zero_number(t_printf *pf);
char			*flag_neg_prec(t_printf *pf, char **str);
char			*flag_pos_prec(t_printf *pf, char **str);
char			*zero_positive_flag(t_printf *pf, char **str);
char			*zero_negative_flag(t_printf *pf, char **str);

/*
** >>-------------------------------- FLOATS --------------------------------<<
*/
char			*get_long_float(t_printf *pf, t_ldbl_cast dbl, t_double_l n);
t_floats		*create_struct(void);
void			float_n_zero(t_floats *flt);
int				valide_float(t_ldbl_cast dbl);
void			error_f(t_printf *pf, t_ldbl_cast dbl);

/*
** >--------< LONG ARITHMETIC >--------<
*/
void			la_multiple(t_floats *flt, int exp);
void			pow_of_2(int *res, int size, int pow);
void			division_by_2(int *tab, int size);
void			addition_tab_rev(int *dst, int *src, int size);

void			part_after_dot(t_floats *flt, int i);
void			la_division(t_floats *flt, int exp);
void			pow_of_5(int *res, int size, int pow);
void			addition_fraction(int *dst, int *src, int size);

/*
** >--------< FLAGS TREATMENT >--------<
*/
char			*float_pos_treatment(t_printf *pf, char **str);
char			*float_zero_treatment(t_printf *pf, char **str);

/*
** >-------< ROUNDUP TREATMENT >-------<
*/
int				plus_five(t_printf *pf, t_floats *flt);
int				check_five(t_floats *flt, int i);
void			plus_one(t_floats *flt);

/*
** >-------< RESULTS TREATMENT >-------<
*/
char			*parts_join(t_ldbl_cast dbl, t_floats *flt, t_printf *pf);
void			is_sign(t_floats *flt);
char			*cut_precision(t_printf *pf, t_floats *flt);
char			*treatment_parts(t_printf *pf, t_floats *flt, char *str);
char			*ft_str_dot_join(char *str1, char *str2);

/*
** >>---------------------------- OTHER FUNCTIONS ----------------------------<<
*/
void			print_width(int hash, int len, t_printf *pf);
void			ft_putnchar(char c, long count);
void			pf_free_floats(t_floats *flt);
/*
** >>-------------------------------- MACROS --------------------------------<<
*/
int				dec_mod(intmax_t n);
intmax_t		dec_abs(intmax_t n);
t_double_l		pf_abs(t_double_l n);
int				pf_zero(int n);

/*
** >>--------------------------------- ITOA ---------------------------------<<
*/
char			*base2(uintmax_t n);
char			*base8(uintmax_t n);
char			*base16(uintmax_t n, int c);
int				get_base_size(uintmax_t n, int base);
char			*ft_ulong_itoa(uintmax_t n, int mod);
int				get_uint_size(uintmax_t len, int mod);
char			*long_int_to_char_rev(int *tab, int size);
char			*long_int_to_char(int *tab, int size);
int				without_zero(int *tab, int size);

/*
**>>--------------------------------- BONUS ---------------------------------<<
*/
void			ft_color(t_printf *pf, int a);

/*
** >-------< BINARY >-------<
*/
void			print_b(t_printf *pf);
char			*treatment_bin(char *str);
int				get_num_space(char *str);

/*
** >-------< ISO TIME >-------<
*/
void			print_k(t_printf *pf);
char			*ft_date(int n, char *str);
char			*ft_date_print(int i, int n, char *str);
int				ft_dayen(int n, int i);
int				ft_day(int day, int flag);
int				ft_month(int ost, int flag);
char			*ft_date_printm(int i, int n, char *str);

#endif
