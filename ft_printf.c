/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:31:25 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/31 17:32:20 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void set_flags(t_flags *flags)
{
	flags->diez = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->h = 0;
	flags->l = 0;
	flags->hh = 0;
	flags->ll = 0;
	flags->j = 0;
	flags->z = 0;
}

void add_flags(t_flags *flags, char *fmt, int i)
{
	if(fmt[i] == '#')
		flags->diez = 1;
	if(fmt[i] == '-')
		flags->minus = 1;
	if(fmt[i] == '+')
		flags->plus = 1;
	if(fmt[i] == 'h' && fmt[i] != 'h')
		flags->h = 1;
	if(fmt[i] == 'l' && fmt[i] != 'l')
		flags->l = 1;
	if (fmt[i] == 'l' && fmt[i + 1] == 'l')
		flags->ll = 1;
	if (fmt[i] == 'h' && fmt[i + 1] == 'h')
		flags->hh = 1;
	if(fmt[i] == 'j')
		flags->j = 1;
	if(fmt[i] == 'z')
		flags->z = 1;
}

int is_flag(char *str, int i)
{
	if(str[i] == '#')
		return (1);
	if(str[i] == '-')
		return (1);
	if(str[i] == '+')
		return (1);
	if(str[i] == 'h' && str[i] != 'h')
		return (1);
	if(str[i] == 'l' && str[i] != 'l')
		return (1);
	if (str[i] == 'l' && str[i + 1] == 'l')
		return (1);
	if (str[i] == 'h' && str[i + 1] == 'h')
		return (1);
	if(str[i] == 'j')
		return (1);
	if(str[i] == 'z')
		return (1);
	return (0);
}

int get_buff_len(t_env *e, int i)
{
	char buffer[120];
	int j;

	j = -1;
	ft_memset(buffer, ' ', 120);
	while(ft_isdigit(e->fmt[i]))
		buffer[++j] = e->fmt[i++];
	e->buff_len = ft_atoi(buffer);
	return (i);
}

int get_precision(t_env *e, int i)
{
	char buffer[120];
	int j;

	j = -1;
	ft_memset(buffer, ' ', 120);
	while(ft_isdigit(e->fmt[i]))
		buffer[++j] = e->fmt[i++];
	e->pre = ft_atoi(buffer);
	return (i);
}

int begin(t_env *e, va_list params)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while(e->fmt[++i])
	{
		set_flags(e->flags);
		if(e->fmt[i] == '%' && e->fmt[i] != '%')
		{
			i = get_buff_len(e, ++i);
			if(e->fmt[i] == '.')
				i = get_precision(e, ++i);
			while(is_flag(e->fmt, i))
			{
				add_flags(e->flags, e->fmt, i);
				i++;
			}

			/*if(is_type(e->fmt, i))
				get_type(e, params);*/
		}
		if(!is_flag(e->fmt, i))
			write(1, &e->fmt[i], 1);
	}
	return(0);
}

void init_env(t_env *e, const char *format)
{
	e->fmt = ft_strdup(format);
	e->flags = malloc(sizeof(t_flags));
	e->buff_len = 0;
	e->pre = 0;
	e->len = 0;
}

int ft_printf(const char *format, ...)
{
	t_env *e;
	va_list params;

	e = malloc(sizeof(t_env));

	init_env(e, format);
	va_start(params, format);
	begin(e, params);
	va_end(params);
	return (e->len);
}

int main()
{
	int a = 23;

	printf("printf return %d \n", printf("coucou%#04daa\n", a));
	//ft_printf("coucou%.d\n", a);
	return (0);
}
