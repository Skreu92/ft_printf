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