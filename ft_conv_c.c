/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:51:11 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/18 18:51:12 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*wchar_handler_ext(wchar_t chr)
{
	char *str;

	str = ft_memset(ft_strnew(4), '\0', 4);
	if (chr <= 0x7F)
		str[0] = chr;
	else if (chr <= 0x7FF)
	{
		str[0] = ((chr >> 6) + 0xC0);
		str[1] = ((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF)
	{
		str[0] = ((chr >> 12) + 0xE0);
		str[1] = (((chr >> 6) & 0x3F) + 0x80);
		str[2] = ((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF)
	{
		str[0] = ((chr >> 18) + 0xF0);
		str[1] = (((chr >> 12) & 0x3F) + 0x80);
		str[2] = (((chr >> 6) & 0x3F) + 0x80);
		str[3] = ((chr & 0x3F) + 0x80);
	}
	return (str);
}

void create_c_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = 1;
	cv->mode = 0;
	if(e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		if(e->pre > 0)
			cv->buffer_nb[e->pre] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if(e->pre > e->buff_len)
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 1));
		cv->buffer_str[e->pre] = '\0';
	}
	else
	{
		cv->mode = 0;
		cv->buffer_str = malloc(sizeof(char) * (len + 1));
		cv->buffer_str[len] = '\0';
		if (len > 0)
			ft_memset(cv->buffer_str, cv->empty, len);
	}		
}

void fill_c_buffer(t_env *e, t_conv *cv, int nb)
{
	int i;

	i = -1;
	if(!e->flags->minus)
	{
		while(++i < ((int)ft_strlen(cv->buffer_str) - 1))
			write(1, &cv->buffer_str[i], 1);
		ft_putchar(nb);
	}
	else
	{
		ft_putchar(nb);
		while(++i < ((int)ft_strlen(cv->buffer_str) - 1))
			write(1, &cv->buffer_str[i], 1);
	}
}

void print_char(char *str, int len)
{
	int i;

	i = -1;
	while(++i < len)
		write(1, &str[i], 1);
}

int ft_conv_c(t_env *e, va_list params, char c)
{
	t_conv *cv;
	int arg;
	int len;
	
	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_len = 0;
	cv->buffer_len = check_c_modifiers(e->modifiers, c);
	create_c_buffer(cv, e);
	if(c == 'c' && e->modifiers->l == 0)
	{
		arg = va_arg(params, int);
		fill_c_buffer(e, cv, arg);
		if (arg == 0 && ft_strlen(cv->buffer_str) == 0)
			return (1);
	}
	else
	{
		arg = (wchar_t)va_arg(params, void *);
		cv->buffer_str = wchar_handler_ext(arg);
		fill_c_buffer(e, cv, arg);
	}
	len = ft_strlen(cv->buffer_str);
	return (len);
}
