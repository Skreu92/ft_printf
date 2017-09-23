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

void f_minus(t_conv *cv, int pre)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (cv->sign == '-')
		cv->buffer_str[i++] = cv->sign;
	else
		cv->buffer_str[i++] = ' ';
	while(cv->mode && i < pre)
	{
		cv->buffer_str[i] = '0';
		i++;
	}
	while(cv->buffer_nb[j] && cv->buffer_str[i])
	{
		cv->buffer_str[i] = cv->buffer_nb[j];
		i++;
		j++;
	}
}

void f_fill_buff(t_conv *cv, int f_plus, int pre, int space)
{
	int i;
	int j;
	int k;

	j = -1;
	k = 1;
	i = 0;
	pre = 1;
	if (cv->mode == 0)
	{
		if(cv->sign == '-' || f_plus == 1)
		{
			cv->buffer_str[0] = cv->sign;
			i++;
		}
		else if (space == 1)
		{
			cv->buffer_str = ft_strjoin(ft_strdup(" "),cv->buffer_str);
			i++;
		}
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
	}
	else
	{
		i = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb);
		if(cv->sign == '-' && !f_plus && cv->empty != '0')
			cv->buffer_str[i - 1] = cv->sign;
		else if ((f_plus == 1 && cv->empty == '0') || (cv->empty == '0' && cv->sign == '-'))
			cv->buffer_str[0] = cv->sign;
		while(i <= pre - (int)ft_strlen(cv->buffer_nb) && pre > 0)
			cv->buffer_str[i++] = '0';
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
	}

	
}
void check_width(t_env *e)
{
	int i;

	i = e->buff_len - e->pre;
	while(i-- > 0)
		write(1, " ", 1);
}

void create_d_buffer(t_conv *cv, t_env *e)
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

void fill_d_minus(t_conv *cv, int f_plus, int pre, int f_space)
{
	int i;
	int j;

	i = -1;
	j = -1;
	(void)f_space;
	(void)pre;
	if (cv->mode == 1)
	{
		if(cv->sign == '-' || f_plus == 1)
			cv->buffer_str[++i] = cv->sign;
		while(i < pre - (int)ft_strlen(cv->buffer_nb) && pre > 0)
			cv->buffer_str[++i] = ' ';
		while(cv->buffer_nb[++j])
			cv->buffer_str[++i] = cv->buffer_nb[j];
		while(cv->buffer_str[++i])
			cv->buffer_str[i] = ' ';
	}
}
int ft_conv_dec(t_env *e, va_list params, char c)
{
	t_conv *cv;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_d_modifiers(e->modifiers, params, c);
	create_d_buffer(cv, e);
	cv->buffer_nb = check_sign(cv);
	if (e->flags->minus)
		fill_d_minus(cv, e->flags->plus, e->pre, e->flags->space);
	else
		f_fill_buff(cv, e->flags->plus, e->pre, e->flags->space);
	ft_putstr(cv->buffer_str);;
	return (ft_strlen(cv->buffer_str));
}
