/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:04:02 by etranchi          #+#    #+#             */
/*   Updated: 2017/10/16 18:04:04 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <locale.h>
#include <limits.h>

int ft_printf(const char *format, ...);

char *setlocal(int categorie, const char *locale);
int main()
{
	int i= 1;
	char *l = setlocale(LC_ALL,"en_US.UTF-8");

	printf("len%d\n", ft_printf("{%S}", NULL));
	printf("len%d\n",printf("{%S}", NULL));
	return (0);
}