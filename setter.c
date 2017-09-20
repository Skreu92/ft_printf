/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 18:08:47 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/04 18:08:49 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void set_flags(t_flags *flags, char *fmt, int i)
{
	if(fmt[i] == '#')
		flags->diez = 1;
	if(fmt[i] == '-')
		flags->minus = 1;
	if(fmt[i] == '+')
		flags->plus = 1;
	if(fmt[i] == ' ')
		flags->space = 1;
	if(fmt[i] == '0')
		flags->zero = 1;
}

int set_modifiers(t_modifiers *modifiers, char *fmt, int i)
{
	if(fmt[i] == 'h' && fmt[i + 1] != 'h')
		modifiers->h = 1;
	if(fmt[i] == 'l' && fmt[i + 1] != 'l')
		modifiers->l = 1;
	if (fmt[i] == 'l' && fmt[i + 1] == 'l')
		modifiers->ll = 1;
	if (fmt[i] == 'h' && fmt[i + 1] == 'h')
		modifiers->hh = 1;
	if(fmt[i] == 'j')
		modifiers->j = 1;
	if(fmt[i] == 'z')
		modifiers->z = 1;
	if(fmt[i] == fmt[i + 1])
		return (i + 2);
	else
		return (i + 1);
}

int set_type(t_env *e, char c, va_list params)
{
	if (c == 's' || c == 'S')
		return (ft_conv_s(e, params, c));
	if (c == 'u' || c == 'U')
		return (ft_conv_u(e, params, c));
	if (c == 'd' || c == 'i' || c == 'D')
		return (ft_conv_dec(e, params, c));
	if (c == 'x' || c == 'X')
		return (ft_conv_x(e, params, c));
	/*if (c == 'c' || c == 'C')
		len += ft_conv_c(e, params, c);*/	
	if (c == 'p')
		return (ft_conv_p(e, params));
	else
		return (0);
}

int set_pourcent(t_env *e)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = malloc(sizeof(char) * 2);
	cv->buffer_nb[1] = '\0';
	cv->buffer_nb[0] = '%';
	create_s_buffer(cv, e);
	if(e->flags->minus)
		fill_s_minus(cv, e->pre);
	else
		fill_s_buffer(cv, e->buff_len, e->pre);
	ft_putstr(cv->buffer_str);
	return (ft_strlen(cv->buffer_str));
}
