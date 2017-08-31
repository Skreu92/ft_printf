/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:31:25 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/31 17:32:20 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	va_list params;

	va_start(params, format);
	printf("%s\n", format);
	int suiv = va_arg(params, int);
	printf("%d\n", suiv);
	va_end(params);
	return (1);
}

int main()
{
	int a = 2;
	char b = 'd';
	ft_printf("coucou", a, b);
	return (0);
}
