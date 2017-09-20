/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 17:08:39 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/16 17:08:41 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *check_d_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;

	if(m->l || c == 'D')
		buffer = ft_lltoa(va_arg(params, long));
	else if(m->ll)
		buffer = ft_lltoa(va_arg(params, long long));
	else if(m->h)
		buffer = ft_itoa((char)va_arg(params, int));
	else if(m->hh)
		buffer = ft_itoa((short)va_arg(params, int));
	else if(m->j)
		 buffer = ft_itoa(va_arg(params, intmax_t));
	else if(m->z)
		buffer = ft_itoa(va_arg(params, size_t));
	else
		buffer = ft_itoa(va_arg(params, int));
	return (buffer);
}

char *check_x_modifiers(t_modifiers *m, va_list params, char c, int diez)
{
	char *buffer;
	char *base;
	char *tmp;
	
	base = (c == 'x') ? ft_strdup("0123456789abcdef") : ft_strdup("0123456789ABCDEF");
	if(m->l || c == 'X')
		buffer = ft_llutoa_base(va_arg(params, unsigned long), base);
	else if(m->ll)
		buffer = ft_llutoa_base(va_arg(params, unsigned long long), base);
	else if(m->h)
		buffer = ft_uitoa_base((unsigned char)va_arg(params, unsigned int), base);
	else if(m->hh)
		buffer = ft_uitoa_base((unsigned short)va_arg(params, unsigned int), base);
	else if(m->j)
		buffer = ft_uitoa_base(va_arg(params, uintmax_t), base);
	else if(m->z)
		buffer = ft_uitoa_base(va_arg(params, size_t), base);
	else
		buffer = ft_uitoa_base(va_arg(params, unsigned int), base);
	if(diez && ft_strcmp(buffer, "0") != 0)
	{
		tmp = (c == 'x') ? "0x" : "0X";
		buffer = ft_strjoin(tmp, buffer);
	}
	return (buffer);

}
char *check_u_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;

	if(m->l || c == 'U')
		buffer = ft_llutoa(va_arg(params, unsigned long long));
	else if(m->ll)
		buffer = ft_llutoa(va_arg(params, unsigned long long));
	else if(m->h)
		buffer = ft_uitoa((unsigned char)va_arg(params, unsigned int));
	else if(m->hh)
		buffer = ft_uitoa((unsigned short)va_arg(params, unsigned int));
	else if(m->j)
		buffer = ft_uitoa(va_arg(params, uintmax_t));
	else if(m->z)
		buffer = ft_uitoa(va_arg(params, size_t));
	else
		buffer = ft_uitoa(va_arg(params, unsigned int));
	return (buffer);	
}

char *check_p_modifiers(t_modifiers *m, va_list params)
{
	char *buffer;
	char *tmp;

	tmp = ft_strdup("0x");
	if(m->l)
		buffer = ft_llutoa_base(va_arg(params, unsigned long), "0123456789abcdef");
	else
		buffer = ft_llutoa_base(va_arg(params, unsigned long long), "0123456789abcdef");
	buffer = ft_strjoin(tmp, buffer);
	free(tmp);
	return (buffer);
}
char *check_c_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;

	if(c == 'c' && m->l == 0)
	{
		buffer = malloc(sizeof(char) * 2);
		buffer[1] = '\0';
		buffer[0] = va_arg(params, int);
	}
	else
	{
		buffer = wchar_handler_ext((wchar_t)va_arg(params, void*));
	}
	return (buffer);
}

void check_s_modifiers(t_conv *cv, t_modifiers *m, va_list params, char c)
{
	cv->buffer_nb = NULL;
	cv->buffer_wnb = NULL;
	if(m->l || c == 'S')
		cv->buffer_wnb = va_arg(params, unsigned int*);
	else
		cv->buffer_nb = va_arg(params, char*);
}
