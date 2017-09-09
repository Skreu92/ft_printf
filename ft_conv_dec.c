/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:42:28 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 16:42:29 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *check_modifiers(t_modifiers *m, va_list params)
{
	char *buffer;

	buffer = ft_itoa(va_arg(params, int));
	if(m->l)
		buffer = ft_lltoa(va_arg(params, long));
	if(m->ll)
		buffer = ft_lltoa(va_arg(params, long long));
	if(m->h)
		buffer = ft_itoa((char)va_arg(params, int));
	if(m->hh)
		buffer = ft_itoa((short)va_arg(params, int));
	if(m->j)
		buffer = ft_itoa(va_arg(params, intmax_t));
	if(m->z)
		buffer = ft_itoa(va_arg(params, size_t));
	return (buffer);
}

char	*check_sign(t_conv *cv)
{
	if(cv->buffer_nb[0] == '-')
	{
		cv->sign = '-';
		return (cv->buffer_nb + 1);
	}
	else
		cv->sign = '+';
	return (cv->buffer_nb);

}
int ft_conv_dec(t_env *e, va_list params)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_modifiers(e->modifiers, params);
	cv->buffer_nb = check_sign(cv);
	create_buffer(cv, e);
	fill_buffer(e->buffer, e->buff_len, e->flags->minus, cv->buffer_nb);
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
