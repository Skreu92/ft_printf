/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:56:30 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 14:56:32 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_lllen(long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int ft_ulllen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int ft_uintlen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int ft_intlen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

char *ft_lltoa(long long n)
{
	char *str;
	int sign;
	int len;
	unsigned long long nb;

	nb = (unsigned long long)n;
	sign = 0;
	if (nb == -9223372036854775808ull)
		return (ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	len = ft_lllen(nb) + sign;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if(sign)
		str[0] = '-';
	return (str);
}

char *ft_llutoa(unsigned long long nb)
{
	char *str;
	int len;

	if (nb == 2147483647)
		return (ft_strdup("-2147483648"));
	len = ft_ulllen(nb);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

char *ft_uitoa(unsigned int nb)
{
	char *str;
	int len;

	if(nb == 4294967295)
		return (ft_strdup("4294967295"));
	len = ft_uintlen(nb);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);		
}

char *ft_itoa(int nb)
{
	char *str;
	int sign;
	int len;

	sign = 0;
	if(nb  == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	len = ft_intlen(nb) + sign;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if(sign)
		str[0] = '-';
	return (str);	
}