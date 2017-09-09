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
	if(e->buff_len > (int)ft_strlen(cv->buffer_nb))
	{
		e->buffer = malloc(sizeof(char) * (e->buff_len + 1));
		e->buffer[e->buff_len] = '\0';
		ft_memset(e->buffer, cv->empty, e->buff_len);
	}
	else if (e->pre > (int)ft_strlen(cv->buffer_nb))
	{
		e->buffer = malloc(sizeof(char) * (e->pre + 1));
		e->buffer[e->pre] = '\0';
		ft_memset(e->buffer, cv->empty, e->pre);
	}
	else
	{
		e->buffer = malloc(sizeof(char) * ((int)ft_strlen(cv->buffer_nb) + 1));
		e->buffer[e->buff_len] = '\0';
		ft_memset(e->buffer, cv->empty, (int)ft_strlen(cv->buffer_nb));
	}
}

void fill_buffer(char *buffer, int buff_len, int flagminus, char *str)
{
	if(flagminus)
		buffer = ft_strncpy(buffer, str, (int)ft_strlen(str));
	else
		buffer = ft_strncpy((buff_len - ft_strlen(str)) + buffer , str, (int)ft_strlen(str));
}
int ft_conv_s(t_env *e, va_list params)
{
	char *str;
	char c;

	c = (e->flags->zero) ? '0' : ' ';
	str = va_arg(params, char *);
	fill_buffer(e->buffer, e->buff_len, e->flags->minus, str);
	ft_putstr(e->buffer);
	return (ft_strlen(e->buffer));
}
