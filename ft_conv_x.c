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

void fill_x_buffer(t_conv *cv, int minus, int diez ,char c)
{
	int i;
	int j;
	char *tmp;

	j = -1;
	tmp = (c == 'X') ? ft_strdup("0X") : ft_strdup("0x");
	if(minus == 1)
	{
		i = 0;
		if(diez && ft_strcmp(cv->buffer_nb, "0") != 0 && ft_strlen(cv->buffer_nb) < ft_strlen(cv->buffer_str))
			while(cv->buffer_str[i] && tmp[i])
			{
				cv->buffer_str[i] = tmp[i];
				i++;
			}
		else if (diez && ft_strcmp(cv->buffer_nb, "0") != 0 )
		{
			cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);
			i = 2;
		}
		while(cv->buffer_nb[i] && cv->buffer_str[i])
		{
			cv->buffer_str[i] = cv->buffer_nb[i];
			i++;
		}

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
		j = 0;
		if (diez && ft_strcmp(cv->buffer_nb, "0") != 0 && ft_strlen(cv->buffer_nb) < ft_strlen(cv->buffer_str))
		{
			cv->buffer_str[(int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) - 2] = tmp[0];
			cv->buffer_str[(int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) - 1] = tmp[1];
		}
		else if (diez && ft_strcmp(cv->buffer_nb, "0") != 0 )
			cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);

	}
}

void create_x_buffer(t_conv *cv, t_env *e)
{
	if(e->buff_len > e->pre && e->buff_len > (int)ft_strlen(cv->buffer_nb))
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);		
	}
	else if(e->pre > e->buff_len && e->pre > (int)ft_strlen(cv->buffer_nb))
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 2));
		cv->buffer_str[e->pre + 1] = '\0';
		ft_memset(cv->buffer_str, '0', e->pre + 1);
	}
	else
	{
		cv->mode = 0;
		cv->buffer_str = malloc(sizeof(char) * ((int)ft_strlen(cv->buffer_nb) + 1));
		cv->buffer_str[(int)ft_strlen(cv->buffer_nb)] = '\0';
		ft_memset(cv->buffer_str, cv->empty, (int)ft_strlen(cv->buffer_nb));
	}
}

int ft_conv_x(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_x_modifiers(e->modifiers, params, c);
	create_x_buffer(cv, e);
	fill_x_buffer(cv, e->flags->minus, e->flags->diez, c);
	ft_putstr(cv->buffer_str);
	return ((int)ft_strlen(cv->buffer_str));
}
