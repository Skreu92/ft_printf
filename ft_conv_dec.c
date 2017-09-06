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

int ft_conv_dec(t_env *e, va_list params)
{
	int nb;
	char c;

	c = (e->flags->zero) ? '0' : ' ';
	nb = va_arg(params, int);
	create_buffer(e, ft_lltoa((long long)nb), c);
	fill_buffer(e->buffer, e->buff_len, e->flags->minus, ft_lltoa((long long)nb));
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
