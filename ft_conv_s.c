/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:02:41 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 15:02:43 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void create_buffer(t_conv *cv, t_env *e, int nb)
{
	int len;

	len = (cv->buffer_nb) ? ft_strlen(cv->buffer_nb) : 0;
	cv->mode = 0;
	if(e->buff_len > (int)ft_strlen(cv->buffer_nb) && e->buff_len > e->pre)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if (e->pre > (int)ft_strlen(cv->buffer_nb))
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 2));
		cv->buffer_str[e->pre + 1] = '\0';
		ft_memset(cv->buffer_str, '0', e->pre + 1);
	}
	else if (nb)
	{
		cv->buffer_str = malloc(sizeof(char) * ((int)ft_strlen(cv->buffer_nb) + 2));
		cv->buffer_str[(int)ft_strlen(cv->buffer_nb) + 1] = '\0';
		ft_memset(cv->buffer_str, cv->empty, (int)ft_strlen(cv->buffer_nb) + 1);
	}
	else if(!nb)
	{
		cv->buffer_str = malloc(sizeof(char) * ((int)ft_strlen(cv->buffer_nb) + 1));
		cv->buffer_str[(int)ft_strlen(cv->buffer_nb)] = '\0';
		ft_memset(cv->buffer_str, cv->empty, (int)ft_strlen(cv->buffer_nb));
	
	}	
}

void create_s_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = (cv->buffer_nb) ? ft_strlen(cv->buffer_nb) : 0;
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
		ft_memset(cv->buffer_str, '0', e->pre);
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

void fill_s_minus(t_conv *cv, int pre)
{
	int i;
	int max;

	i = -1;
	if(cv->mode == 1)
	{
		max = (pre) ? pre : ft_strlen(cv->buffer_nb);
		while(++i < max && cv->buffer_nb[i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 2)
	{
		while(cv->buffer_str[++i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if(cv->mode == 0)
		ft_strcpy(cv->buffer_str, cv->buffer_nb);
}
void fill_s_buffer(t_conv *cv)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if(cv->mode == 1)
	{
		j = ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb);
		while(cv->buffer_nb[++i])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
	if(cv->mode == 2)
	{
		while(cv->buffer_str[++i]) 
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if(cv->mode == 0)
	{
		j = ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb) - 1;
		while(cv->buffer_nb[++i] && cv->buffer_str[i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
}

int ft_conv_s(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = ' ';
	check_s_modifiers(cv, e->modifiers, params, c);
	if (!cv->buffer_nb)
		cv->buffer_nb = NULL;
	if(!e->modifiers->l)
	{
		create_s_buffer(cv, e);
		if(e->flags->minus)
			fill_s_minus(cv, e->pre);
		else
			fill_s_buffer(cv);
	}
	else
	{
		//create_S_buffer(cv, e);
		printf("ici %d\n", (int)cv->buffer_wnb);
	}
	ft_putstr(cv->buffer_str);
	return (ft_strlen(cv->buffer_str));
}
