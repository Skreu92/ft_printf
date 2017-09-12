/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 15:00:12 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/04 15:00:16 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int get_precision(t_env *e, int i)
{
	char buff[10];
	int j;

	j = -1;
	ft_memset(buff, ' ', 3);
	while(ft_isdigit(e->fmt[i]))
		buff[++j] = e->fmt[i++];
	printf("%s\n", buff);
	e->pre = ft_atoi(buff);

	return (i);
}

int get_buff_len(t_env *e, int i, int *len)
{
	char buffer[10];
	int j;

	j = -1;
	ft_memset(buffer, ' ', 3);
	while(ft_isdigit(e->fmt[i]))
		buffer[++j] = e->fmt[i++];
	*len = ft_atoi(buffer);
	return (i);
}

void init_flags_modi(t_flags *flags, t_modifiers *modifiers)
{
	flags->diez = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	modifiers->h = 0;
	modifiers->l = 0;
	modifiers->hh = 0;
	modifiers->ll = 0;
	modifiers->j = 0;
	modifiers->z = 0;
}



