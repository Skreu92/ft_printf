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


void fill_u(t_conv *cv, int pre, int minus)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (cv->mode == 0)
		while(cv->buffer_nb[++j])
			cv->buffer_str[++i] = cv->buffer_nb[j];
	if (cv->mode == 1)
	{
		i = (minus == 1) ? -1 :(int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) - 1;
		if(pre > 0)
		{	while((pre - cv->buffer_len) > 0 && (pre - ft_strlen(cv->buffer_str)) > 0 && ++j < (pre - cv->buffer_len))
				cv->buffer_str[++i] = '0';
			i--;
		}
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[++i] = cv->buffer_nb[j];
	}
	if(cv->mode == 2)
	{
		i = 0;
		if(pre > 0)
			while((pre - cv->buffer_len) > 0 && ++j < (pre - cv->buffer_len))
				cv->buffer_str[i++] = '0';
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
	}
}

int ft_conv_u(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_u_modifiers(e->modifiers, params, c);
	cv->buffer_len = (int)ft_strlen(cv->buffer_nb);
	create_d_buffer(cv, e);
	fill_u(cv, e->pre, e->flags->minus);
	ft_putstr(cv->buffer_str);
	return (ft_strlen(cv->buffer_str));
}
