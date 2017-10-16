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

int		ft_wlen(unsigned int w)
{
	int i;
	int sb;

	i = 1;
	sb = ft_size_bin(w);
	while (sb - 8 >= 0)
	{
		sb -= 8;
		i++;
	}
	return (i);
}

void	create_s_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = ft_strlen(cv->buffer_nb);
	if (e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if (e->pre > e->buff_len)
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

void	fill_s_minus(t_conv *cv, int pre)
{
	int i;
	int max;

	i = -1;
	if (cv->mode == 1)
	{
		max = (pre) ? pre : ft_strlen(cv->buffer_nb);
		while (++i < max && cv->buffer_nb[i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 2)
	{
		while (cv->buffer_str[++i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 0)
		ft_strcpy(cv->buffer_str, cv->buffer_nb);
}

void	fill_s_buffer(t_conv *cv, int pre)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (cv->mode == 1)
	{
		j = ft_strlen(cv->buffer_str);
		j -= (pre > 0) ? pre : (int)ft_strlen(cv->buffer_nb);
		i = -1;
		while (cv->buffer_nb[++i] && cv->buffer_str[j])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
	if (cv->mode == 2)
	{
		while (cv->buffer_str[++i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 0)
	{
		j = ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb) - 1;
		while (cv->buffer_nb[++i] && cv->buffer_str[i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
}

int		putws(t_env *e, unsigned int *buff, int len)
{
	if (MB_CUR_MAX > 1)
	{
		e->pre = (e->pre == 0) ? 320 : e->pre;
		while (*buff && len < e->pre)
		{
			ft_putwchar(*buff);
			len += ft_wlen(*buff);
			buff++;
		}
	}
	else
		return (0);
	return (len);
}

void	put_little_s(t_env *e, t_conv *cv, int *len, int nul)
{
	create_s_buffer(cv, e);
	if (e->flags->minus)
		fill_s_minus(cv, e->pre);
	else
		fill_s_buffer(cv, e->pre);
	if (cv->buffer_nb && ft_strcmp("(null)", cv->buffer_nb) == 0 && nul == 1)
		free(cv->buffer_nb);
	ft_putstr(cv->buffer_str);
	*len += ft_strlen(cv->buffer_str);
	free(cv->buffer_str);
}

void	put_big_s(t_env *e, t_conv *cv, int *len)
{
	if (cv->buffer_wnb == 0 || cv->buffer_wnb == NULL)
	{
		cv->buffer_str = ft_strdup("(null)");
	}
	else if (cv->buffer_wnb != NULL)
	{
		*len = putws(e, (unsigned int *)cv->buffer_wnb, 0);
	}
}

int		ft_conv_s(t_env *e, va_list params, char c)
{
	t_conv	*cv;
	int		len;
	int		nul;

	nul = 0;
	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	len = 0;
	check_s_modifiers(cv, e->modifiers, params, c);
	if (cv->buffer_nb == NULL && (e->pre > 0 || e->buff_len > 0))
		cv->buffer_nb = ft_strdup("");
	else if (cv->buffer_nb == NULL && e->pre == 0 && (c == 's'
		&& e->modifiers->l == 0))
	{
		cv->buffer_nb = ft_strdup("(null)");
		nul++;
	}
	if (e->modifiers->l == 0 && c != 'S')
		put_little_s(e, cv, &len, nul);
	else
		put_big_s(e, cv, &len);
	free(cv);
	return (len);
}
