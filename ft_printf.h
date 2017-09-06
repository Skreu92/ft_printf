/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:32:27 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/31 17:33:01 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define UINT_MAX 4294967295;

# include "libft/libft.h"
# include <stdarg.h>
# include <sys/types.h>
# include <stdio.h>

typedef struct s_flags
{
	int diez;
	int minus;
	int plus;
	int space;
	int zero;
}			t_flags;

typedef struct s_modifiers
{
	int h;
	int l;
	int hh;
	int ll;
	int j;
	int z;
}				t_modifiers;

typedef struct s_types
{
	int s;
	int S;
	int u;
	int U;
	int d;
	int D;
	int x;
	int X;
	int c;
	int C;
	int p;
	int i;
}			t_types;

typedef struct s_env
{
	char *fmt;
	char *buffer;
	int len;
	int buff_len;
	int pre;
	t_flags *flags;
	t_modifiers *modifiers;
	t_types  *types;
}				t_env;

int		get_precision(t_env *e, int i);
int		get_buff_len(t_env *e, int i);
void	init_env(t_env *e, const char *format);
int 	is_flag(char *str, int i);
int 	is_modifier(char *str, int i);
int 	is_type(char c);
int		set_modifiers(t_modifiers *modifiers, char *fmt, int i);
void 	set_flags(t_flags *flags, char *fmt, int i);
int		set_type(t_env *e, char c, va_list params);
void 	init_flags_modi(t_flags *flags, t_modifiers *modifiers);
int ft_conv_s(t_env *e, va_list params);


char *ft_lltoa(long long nb);
char *ft_llutoa(unsigned long long nb);
int ft_conv_dec(t_env *e, va_list params);
int ft_conv_u(t_env *e, va_list params);
void create_buffer(t_env *e, char *str, char c);
void fill_buffer(char *buffer, int buff_len, int flagminus, char *str);
char *ft_uitoa(unsigned int nb);
char *ft_itoa( int nb);
#endif
