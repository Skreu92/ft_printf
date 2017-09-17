/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:39:39 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/17 18:39:40 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_conv_x(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_x_modifiers(e->modifiers, params, c);
	create_buffer(cv, e, 1);
	f_fill_buff(cv, e->flags->plus, e->pre, e->buff_len);
	ft_putstr(cv->buffer_nb);
	return (ft_strlen(cv->buffer_str));
}
