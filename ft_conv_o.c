/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 20:43:32 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/22 20:43:34 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void diez_o(t_conv *cv)
{
	char *tmp;

	tmp = ft_strdup("0");
	cv->buffer_nb = ft_strjoin(tmp, cv->buffer_nb);
}

void create_o_buffer(t_conv *cv, t_env *e)
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

void fill_o_minus(t_conv *cv, t_flags *flags, int pre)
{
	int i;
	int j;
   
   	i = 0;
	j = -1;
	if(cv->mode == 0)
	{

	}
	if(cv->mode == 1)
	{
		if(cv->sign == '-' && flags->plus == 0 && cv->empty != '0')
			cv->buffer_str[i++] = cv->sign;
		else if ((flags->plus == 1 && cv->empty == '0'))
			cv->buffer_str[i++] = cv->sign;
		else if (flags->plus == 1)
			cv->buffer_str[i++] = cv->sign;
		else if ((cv->empty == '0' && cv->sign == '-'))
			cv->buffer_str[i++] = cv->sign;
		else if ((cv->empty == '0' && cv->sign == '+' && pre > 0) || ft_strcmp("0", cv->buffer_nb) == 0)
			cv->buffer_str[i++] = ' ';
		if(pre > (int)ft_strlen(cv->buffer_nb))
		{	
			if(cv->sign == '-' && flags->plus == 0 && cv->empty != '0')
				cv->buffer_str[i++] = cv->sign;
			while(i < (pre - (int)ft_strlen(cv->buffer_nb)))
				cv->buffer_str[i++] = '0';
		}
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
		while(cv->buffer_str[i])
			cv->buffer_str[i++] = ' ';
	}
	if(cv->mode == 2)
	{
		i = pre - (int)ft_strlen(cv->buffer_nb);
		if(cv->sign == '-' && !flags->plus && cv->empty != '0')
			cv->buffer_str[i - 1] = cv->sign;
		else if ((flags->plus == 1 && cv->empty == '0') || (cv->empty == '0' && cv->sign == '-'))
			cv->buffer_str[0] = cv->sign;
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
		if (pre == (int)ft_strlen(cv->buffer_str) && cv->sign == '-')
			cv->buffer_str = ft_strjoin("-",cv->buffer_str); 
	}
}

void fill_o_buffer(t_conv *cv, int f_plus, int pre, int f_space)
{
	int i;
	int j;
	int k;

	j = -1;
	k = 1;
	i = 0;
	(void)f_space;
	if (cv->mode == 0)
	{
		if(cv->sign == '-')
		{
			cv->buffer_str[0] = cv->sign;
			i++;
		}
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
		cv->buffer_str[i] = '\0';
	}
	if(cv->mode == 2)
	{
		i = 0;
		if(cv->sign == '-' && !f_plus && cv->empty != '0')
			cv->buffer_str[i++] = cv->sign;
		else if ((f_plus == 1 && cv->empty == '0') || (cv->empty == '0' && cv->sign == '-'))
			cv->buffer_str[i++] = cv->sign;
		else if(cv->sign == '-')
		{
			cv->buffer_str = ft_strjoin("-", cv->buffer_str);
			i++;
		}
		if(pre > 0)
			while((pre - cv->buffer_len) > 0 && ++j < (pre - (int)ft_strlen(cv->buffer_nb)))
				cv->buffer_str[i++] = '0';
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[i++] = cv->buffer_nb[j];
		cv->buffer_str[i] = '\0';
		if (pre == (int)ft_strlen(cv->buffer_str) && cv->sign == '-')
			cv->buffer_str = ft_strjoin("-",cv->buffer_str); 
	}
	if(cv->mode == 1)
	{
		i = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) - 1;
		if(cv->sign == '-' && f_plus == 0 && cv->empty != '0')
			cv->buffer_str[i] = cv->sign;
		else if ((f_plus == 1 && cv->empty == '0'))
			cv->buffer_str[0] = cv->sign;
		else if (f_plus == 1)
			cv->buffer_str[i - 1] = cv->sign;
		else if ((cv->empty == '0' && cv->sign == '-'))
			cv->buffer_str[0] = cv->sign;
		else if ((cv->empty == '0' && cv->sign == '+' && pre > 0) || ft_strcmp("0", cv->buffer_nb) == 0)
			cv->buffer_str[0] = ' ';
		if(pre > (int)ft_strlen(cv->buffer_nb))
		{	
			i = (int)ft_strlen(cv->buffer_str) - pre;
			if(cv->sign == '-' && f_plus == 0 && cv->empty != '0')
				cv->buffer_str[i - 1] = cv->sign;
			while((pre - cv->buffer_len) > 0 && (pre - ft_strlen(cv->buffer_str)) > 0 && i < ((int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb)))
				cv->buffer_str[i++] = '0';
			i--;
		}
		j = -1;
		while(cv->buffer_nb[++j])
			cv->buffer_str[++i] = cv->buffer_nb[j];
	}	
}

int ft_conv_o(t_env *e, va_list params, char c)
{
	t_conv *cv;
	int len;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_o_modifiers(e->modifiers, params, c);
	if((e->flags->point == 1 && e->pre == 0 && ft_strcmp("0",cv->buffer_nb) == 0 )|| cv->buffer_nb == NULL)
		cv->buffer_nb = ft_strdup("");
	create_o_buffer(cv, e);
	if(cv->buffer_nb != NULL)
	{
		if(e->flags->diez && ft_strcmp(cv->buffer_nb, "0") != 0 )
			diez_o(cv);
		if (e->flags->minus == 1)
			fill_o_minus(cv, e->flags, e->pre);
		else
			fill_o_buffer(cv, e->flags->plus, e->pre, e->flags->space);
	}
	ft_putstr(cv->buffer_str);
	len = ft_strlen(cv->buffer_str);
	return (len);
}