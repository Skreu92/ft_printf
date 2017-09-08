/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:38:49 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 17:38:50 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_conv_u(t_env *e, va_list params)
{
	char c;
	unsigned int nb;

	c = (e->flags->zero) ? '0' : ' ';
	nb = va_arg(params, unsigned int);
	create_buffer(e, ft_uitoa(nb), c);
	fill_buffer(e->buffer, e->buff_len, e->flags->minus, ft_uitoa(nb));
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
