/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 18:08:47 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/04 18:08:49 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void set_flags(t_flags *flags, char *fmt, int i)
{
	if(fmt[i] == '#')
		flags->diez = 1;
	if(fmt[i] == '-')
		flags->minus = 1;
	if(fmt[i] == '+')
		flags->plus = 1;
	if(fmt[i] == ' ')
		flags->space = 1;
	if(fmt[i] == '0')
		flags->zero = 1;
}

int set_modifiers(t_modifiers *modifiers, char *fmt, int i)
{
	if(fmt[i] == 'h' && fmt[i + 1] != 'h')
		modifiers->h = 1;
	if(fmt[i] == 'l' && fmt[i + 1] != 'l')
		modifiers->l = 1;
	if (fmt[i] == 'l' && fmt[i + 1] == 'l')
		modifiers->ll = 1;
	if (fmt[i] == 'h' && fmt[i + 1] == 'h')
		modifiers->hh = 1;
	if(fmt[i] == 'j')
		modifiers->j = 1;
	if(fmt[i] == 'z')
		modifiers->z = 1;
	if(fmt[i] == fmt[i + 1])
		return (i + 2);
	else
		return (i + 1);
}

void set_type(t_types *types, char c)
{
	if (c == 's')
		types->s = 1;
	if (c == 'S')
		types->S = 1;
	if (c == 'u')
		types->u = 1;
	if (c == 'U')
		types->U = 1;
	if (c == 'd')
		types->d = 1;
	if (c == 'D')
		types->D = 1;
	if (c == 'x')
		types->x = 1;
	if (c == 'X')
		types->X = 1;
	if (c == 'c')
		types->c = 1;
	if (c == 'C')
		types->C = 1;
	if (c == 'p')
		types->p = 1;
	if (c == 'i')
		types->i = 1;
}
