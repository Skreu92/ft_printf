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

int ft_conv_u(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_u_modifiers(e->modifiers, params, c);
	create_buffer(cv, e, 1);
	f_fill_buff(cv, e->flags->plus, e->pre, e->flags->space);
	ft_putstr(cv->buffer_str);
	return (ft_strlen(cv->buffer_str));
}
