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

	buffer = xft_itoa(va_arg(params, int));
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
int ft_conv_dec(t_env *e, va_list params)
{
	char c;
	char *buffer;

	c = (e->flags->zero) ? '0' : ' ';
	buffer = check_modifiers(e->modifiers, params);
	create_buffer(e, buffer, c);
	printf("aaa%s\n",e->buffer );
	fill_buffer(e->buffer, e->buff_len, e->flags->minus, buffer);
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
