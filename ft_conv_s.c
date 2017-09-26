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


static void		wide_to_char(wchar_t **tmp, char **s1, char **s2, int i)
{
	while ((*tmp) && (*tmp)[++i])
	{
		*s1 = ft_memset(ft_strnew(5), '\0', 5);
		if ((*tmp)[i] <= 0x7F)
			(*s1)[0] = (*tmp)[i];
		else if ((*tmp)[i] <= 0x7FF)
		{
			(*s1)[0] = (((*tmp)[i] >> 6) + 0xC0);
			(*s1)[1] = (((*tmp)[i] & 0x3F) + 0x80);
		}
		else if ((*tmp)[i] <= 0xFFFF)
		{
			(*s1)[0] = (((*tmp)[i] >> 12) + 0xE0);
			(*s1)[1] = ((((*tmp)[i] >> 6) & 0x3F) + 0x80);
			(*s1)[2] = (((*tmp)[i] & 0x3F) + 0x80);
		}
		else if ((*tmp)[i] <= 0x10FFFF)
		{
			(*s1)[0] = (((*tmp)[i] >> 18) + 0xF0);
			(*s1)[1] = ((((*tmp)[i] >> 12) & 0x3F) + 0x80);
			(*s1)[2] = ((((*tmp)[i] >> 6) & 0x3F) + 0x80);
			(*s1)[3] = (((*tmp)[i] & 0x3F) + 0x80);
		}
		*s2 = ft_strjoin(*s2, *s1);
	}
	if(i == 0)
		*s2 = ft_strdup("");
}

void create_s_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = ft_strlen(cv->buffer_nb);
	cv->mode = 0;
	if(e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
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

void fill_s_buffer(t_conv *cv, int pre)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if(cv->mode == 1)
	{
		j = ft_strlen(cv->buffer_str);
		j -= (pre > 0) ? pre : (int)ft_strlen(cv->buffer_nb);
		i = -1; 
		while(cv->buffer_nb[++i] && cv->buffer_str[j])
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

void			wstring_range_handler(int range, char **str, int minus)
{
	char	*tmp;
	int		n;

	tmp = NULL;
	if(!*str)
		n = 0;
	else
		n = range - (int)ft_strlen(*str);
	if (n > 0)
	{
		tmp = ft_memset(ft_strnew(n), ' ', n);
		(*str) = (minus == 1) ? ft_strjoin(*str, tmp): ft_strjoin(tmp, *str);
	}
}

int ft_conv_s(t_env *e, va_list params, char c)
{
	t_conv *cv;
	int len;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	len = 0;
	check_s_modifiers(cv, e->modifiers, params, c);
	if(cv->buffer_nb == NULL && (e->pre > 0 || e->buff_len > 0))
		cv->buffer_nb = ft_strdup("");
	else if (cv->buffer_nb == NULL && e->pre == 0)
		cv->buffer_nb = ft_strdup("(null)");
	if(e->modifiers->l == 0 && c != 'S')
	{
		create_s_buffer(cv, e);
		if(e->flags->minus)
			fill_s_minus(cv, e->pre);
		else
			fill_s_buffer(cv, e->pre);
	}
	else if (!(MB_CUR_MAX < 1))
	{
		if (cv->buffer_wnb == NULL || cv->buffer_wnb == 0)
			cv->buffer_str = ft_strdup("(null)");
		else if (cv->buffer_wnb )
		{
			wide_to_char(&cv->buffer_wnb, &cv->buffer_nb, &cv->buffer_str, -1);
			wstring_range_handler(e->pre, &cv->buffer_str, e->flags->minus);
		}
	}
	ft_putstr(cv->buffer_str);
	len += ft_strlen(cv->buffer_str);
	return (len);
}
