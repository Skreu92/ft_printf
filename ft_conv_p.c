/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 14:50:29 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/19 14:50:31 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void fill_p_buffer(t_conv *cv)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if(cv->mode == 1)
	{
		cv->buffer_nb = ft_strjoin("0x", cv->buffer_nb);
		j = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb);
		while(cv->buffer_nb[++i])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
	if(cv->mode == 2)
	{
		j = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb);
		while(cv->buffer_nb[++i])
			cv->buffer_str[j++] = cv->buffer_nb[i];
		cv->buffer_str = ft_strjoin("0x", cv->buffer_str);
	}
	if( cv->mode == 0)
	{
		while(cv->buffer_nb[++i] != '\0')
			cv->buffer_str[i] = cv->buffer_nb[i];
		cv->buffer_str = ft_strjoin("0x", cv->buffer_str);
	}
}

void fill_p_minus_buffer(t_conv *cv)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if(cv->mode == 1)
	{
		cv->buffer_nb = ft_strjoin("0x", cv->buffer_nb);
		j = 0;
		while(cv->buffer_nb[++i])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
	if(cv->mode == 2)
	{
		j = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb);
		while(cv->buffer_nb[++i])
			cv->buffer_str[j++] = cv->buffer_nb[i];
		cv->buffer_str = ft_strjoin("0x", cv->buffer_str);
	}
	if( cv->mode == 0)
	{
		while(cv->buffer_nb[++i] != '\0')
			cv->buffer_str[i] = cv->buffer_nb[i];
		cv->buffer_str = ft_strjoin("0x", cv->buffer_str);
	}
}

int ft_conv_p(t_env *e, va_list params)
{
	t_conv *cv;
	int len;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero == 1) ? '0' : ' ';
	cv->buffer_nb = check_p_modifiers(e->modifiers, params);
	if((e->flags->point == 1 && e->pre == 0) || cv->buffer_nb == NULL)
		cv->buffer_nb = ft_strdup("");
	create_d_buffer(cv, e);
	if(e->flags->minus == 1)
		fill_p_minus_buffer(cv);
	else
		fill_p_buffer(cv);
	ft_putstr(cv->buffer_str);
	len = ft_strlen(cv->buffer_str);
	return (len);
}
