/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 20:09:16 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/18 20:09:18 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_mask1(wchar_t n)
{
	char	*str;

	str = ft_strnew(1);
	str[0] = n;
	str[1] = '\0';
	return (str);
}

char	*ft_mask2(wchar_t n)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;

	str = ft_strnew(2);
	str[3] = '\0';
	a = 0x3F & n;
	n <<= 2;
	b = 0x1F00 & n;
	b = b | a | 0xC080;
	str[1] = b;
	str[0] = b >> 8;
	return (str);
}

char	*ft_mask3(wchar_t n)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	str = ft_strnew(3);
	str[4] = '\0';
	a = 0x3F & n;
	n <<= 2;
	b = 0x3F00 & n;
	n <<= 2;
	c = 0xF0000 & n;
	b = b | a | c | 0xE08080;
	str[2] = b;
	str[1] = b >> 8;
	str[0] = b >> 16;
	return (str);
}

char	*ft_mask4(wchar_t n)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;

	str = ft_strnew(4);
	str[5] = '\0';
	a = 0x3F & n;
	n <<= 2;
	b = 0x3F00 & n;
	n <<= 2;
	c = 0xF0000 & n;
	n <<= 2;
	d = 0x7000000 & n;
	b = b | a | c | d | 0xF0808080;
	str[4] = b;
	str[3] = b >> 8;
	str[2] = b >> 16;
	str[1] = b >> 24;
	return (str);
}
