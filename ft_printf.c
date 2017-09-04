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


void print_struct(t_env *e)
{
	printf("flag diez %d\n", e->flags->diez);
	printf("flag minus %d\n", e->flags->minus);
	printf("flag plus %d\n", e->flags->plus);
	printf("flag space %d\n", e->flags->space);
	printf("flag zero %d\n", e->flags->zero);
	printf("modifiers h %d\n", e->modifiers->h);
	printf("modifiers l %d\n", e->modifiers->l);
	printf("modifiers hh %d\n", e->modifiers->hh);
	printf("modifiers ll %d\n", e->modifiers->ll);
	printf("modifiers j %d\n", e->modifiers->j);
	printf("modifiers z %d\n", e->modifiers->z);
	printf("precison %d\n", e->pre);
	printf("buff_len %d\n",e->buff_len);
}

int begin(t_env *e, va_list params)
{
	int i;
	int j;

	i = -1;
	j = -1;
	(void)params;
	while(e->fmt[++i])
	{
		init_flags_modi(e->flags, e->modifiers);
		if(e->fmt[i] == '%')
		{
			while(e->fmt[i + 1] && is_flag(e->fmt, ++i))
				set_flags(e->flags, e->fmt, i);
			i = get_buff_len(e, i);
			if(e->fmt[i++] == '.')
				i = get_precision(e, i);
			if(e->fmt[i] && is_modifier(e->fmt, i))
				i = set_modifiers(e->modifiers, e->fmt, i);
			if(is_type(e->fmt[i]))
				set_type(e->types, e->fmt[i]);
			print_struct(e);
		}
		else
			write(1, &e->fmt[i], 1);
	}
	return(i);
}



int ft_printf(const char *format, ...)
{
	t_env *e;
	va_list params;

	e = malloc(sizeof(t_env));

	init_env(e, format);
	va_start(params, format);
	e->len = begin(e, params);
	va_end(params);
	return (e->len);
}

void init_env(t_env *e, const char *format)
{
	e->fmt = ft_strdup(format);
	e->flags = malloc(sizeof(t_flags));
	e->modifiers = malloc(sizeof(t_modifiers));
	e->types = malloc(sizeof(t_types));
	e->buff_len = 0;
	e->pre = 0;
	e->len = 0;
}

int main()
{
	int a = 23;

	printf("printf return %d \n", printf("coucou%-+3.50ddaa\n", a));
	ft_printf("coucou%#-+3.50hd");
	return (0);
}
