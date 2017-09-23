/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:39:39 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/17 18:39:40 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void fill_x_buffer(t_conv *cv, int minus, int diez)
{
	int i;
	int j;

	if(minus == 1)
	{
		i = 0;
		j = (diez) ? 1 : -1;
		while(cv->buffer_nb[i] && cv->buffer_str[++j])
		{
			cv->buffer_str[j] = cv->buffer_nb[i];
			i++;
		}
		if(!cv->buffer_nb[i])
			j++;
		while(cv->buffer_str[j])
			cv->buffer_str[j++] = ' ';
	}
	else
	{
		i = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb);
		j = -1;
		while(i < (int)ft_strlen(cv->buffer_str) && cv->buffer_nb[++j])
		{
			cv->buffer_str[i] = cv->buffer_nb[j]; 
			i++;
		}
		while(cv->buffer_str[i])
			cv->buffer_str[i++] = cv->empty;

	}
}

void create_x_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = (cv->buffer_nb) ? ft_strlen(cv->buffer_nb) : 0;
	if(e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);		
	}
	else if(e->pre > e->buff_len && e->pre > len)
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 2));
		cv->buffer_str[e->pre + 1] = '\0';
		ft_memset(cv->buffer_str, '0', e->pre + 1);
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

void diez(t_env *e, t_conv *cv, char c)
{
	char *tmp;

	tmp = (c == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	if(ft_strlen(cv->buffer_str) > ft_strlen(cv->buffer_nb) && e->flags->minus)
	{
		cv->buffer_str[0] = tmp[0];
		cv->buffer_str[1] = tmp[1];
	}
	else if(ft_strlen(cv->buffer_str) > ft_strlen(cv->buffer_nb) && !e->flags->minus)
	{
		if(e->flags->zero)
		{
			cv->buffer_str[0] = tmp[0];
			cv->buffer_str[1] = tmp[1];
		}
		else
		{
			cv->buffer_str[ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb) - 2] = tmp[0];
			cv->buffer_str[ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb) - 1] = tmp[1];		
		}
	}
	else if(ft_strlen(cv->buffer_nb) == ft_strlen(cv->buffer_str))
		cv->buffer_str = ft_strjoin(tmp, cv->buffer_nb);

}

int ft_conv_x(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_x_modifiers(e->modifiers, params, c);
	if(e->flags->point == 1 && e->pre == 0)
		cv->buffer_nb = NULL;
	create_x_buffer(cv, e);
	if(cv->buffer_nb != NULL)
	{
		fill_x_buffer(cv, e->flags->minus, e->flags->diez);
		if(e->flags->diez && ft_strcmp(cv->buffer_nb, "0") != 0 )
			diez(e, cv, c);
	}
	ft_putstr(cv->buffer_str);
	return ((int)ft_strlen(cv->buffer_str));
}
