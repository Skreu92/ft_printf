/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:02:41 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 15:02:43 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void create_buffer(t_conv *cv, t_env *e)
{
	cv->mode = 0;
	if(e->buff_len > (int)ft_strlen(cv->buffer_nb) && e->buff_len > e->pre)
	{
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len));
		cv->buffer_str[e->buff_len - 1] = '\0';
		cv->mode = 1;
		ft_memset(cv->buffer_str, cv->empty, e->buff_len - 1);
	}
	else if (e->pre > (int)ft_strlen(cv->buffer_nb))
	{
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 2));
		cv->buffer_str[e->pre + 1] = '\0';
		cv->mode = 2;
		ft_memset(cv->buffer_str, cv->empty, e->pre + 1);
	}
	else
	{
		cv->buffer_str = malloc(sizeof(char) * ((int)ft_strlen(cv->buffer_nb) + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, (int)ft_strlen(cv->buffer_nb));
	}
}


int ft_conv_s(t_env *e, va_list params)
{
	char *str;
	char c;

	c = (e->flags->zero) ? '0' : ' ';
	str = va_arg(params, char *);
	//fill_buffer(e->buffer, e->buff_len, e->flags->minus, str);
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
