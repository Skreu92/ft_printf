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

int ft_conv_p(t_env *e, va_list params)
{
	t_conv *cv;
	int len;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_p_modifiers(e->modifiers, params); 
	ft_putstr(cv->buffer_nb);
	len = ft_strlen(cv->buffer_nb);
	return (len);
}
