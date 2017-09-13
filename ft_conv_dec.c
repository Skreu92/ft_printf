/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:42:28 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 16:42:29 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *check_modifiers(t_modifiers *m, va_list params)
{
	char *buffer;

	buffer = ft_itoa(va_arg(params, int));
	if(m->l)
		buffer = ft_lltoa(va_arg(params, long));
	if(m->ll)
		buffer = ft_lltoa(va_arg(params, long long));
	if(m->h)
		buffer = ft_itoa((char)va_arg(params, int));
	if(m->hh)
		buffer = ft_itoa((short)va_arg(params, int));
	if(m->j)
		buffer = ft_itoa(va_arg(params, intmax_t));
	if(m->z)
		buffer = ft_itoa(va_arg(params, size_t));
	return (buffer);
}

char	*check_sign(t_conv *cv)
{
	int i;

	i = 0;
	while((cv->buffer_nb[i] >= '0' && cv->buffer_nb[i] <= '9') || cv->buffer_nb[i] == '-' || cv->buffer_nb[i] == '+')
		i++;
	cv->buffer_nb[i] = '\0';
	if(cv->buffer_nb[0] == '-')
	{
		cv->sign = '-';
		return (cv->buffer_nb + 1);
	}
	else
		cv->sign = '+';
	return (cv->buffer_nb);

}

void f_minus(t_conv *cv, int f_plus)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (f_plus || cv->sign == '-')
		cv->buffer_str[0] = cv->sign;
	if (cv->sign != '+')
		i++;
	while(cv->mode && i < ((int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb)))
	{
		cv->buffer_str[i] = '0';
		i++;
	}
	while(cv->buffer_nb[j])
	{
		cv->buffer_str[i] = cv->buffer_nb[j];
		i++;
		j++;
	}
}

void f_fill_buff(t_conv *cv, int f_plus)
{
	int i;
	int j;
	int k;

	i = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) + 1;
	j = 0;
	k = 1;
	if (cv->mode == 1)
	{
		cv->buffer_str[i - 1] = (f_plus) ? cv->sign : cv->empty;
	}
	else if (cv->mode == 2)
	{
		cv->buffer_str[0] = (f_plus) ? cv->sign : cv->empty;
	}
	else if(f_plus || cv->sign == '-')
		cv->buffer_str[(int)ft_strlen(cv->buffer_nb) - 1] = cv->sign;
	if(cv->mode == 2)
	{
		while(k < i)
		{
			cv->buffer_str[k] = '0';
			k++;
		}
	}
	while(i < (int)ft_strlen(cv->buffer_str))
	{
		cv->buffer_str[i] = cv->buffer_nb[j];
		i++;
		j++;
	}
}
void check_width(t_env *e)
{
	int i;

	i = e->buff_len - e->pre;
	while(i-- > 0)
		write(1, " ", 1);
}
int ft_conv_dec(t_env *e, va_list params)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_modifiers(e->modifiers, params);
	create_buffer(cv, e);
	cv->buffer_nb = check_sign(cv);
	if(e->flags->minus)
		f_minus(cv, e->flags->plus);
	else
		f_fill_buff(cv, e->flags->plus);
	ft_putstr(cv->buffer_str);
	check_width(e);
	return (ft_strlen(cv->buffer_str));
}
