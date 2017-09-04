/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 15:02:37 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/04 15:02:39 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int is_flag(char *str, int i)
{
	if(str[i] == '#')
		return (1);
	if(str[i] == '-')
		return (1);
	if(str[i] == '+')
		return (1);
	if(str[i] == ' ')
		return (1);
	if(str[i] == '0')
		return (1);
	return (0);
}

int is_type(char *str, int i)
{
	if(str[i] == 's' || str[i] == 'S')
		return (1);
	if(str[i] == 'u' || str[i] == 'U')
		return (1);
	if(str[i] == 'd' || str[i] == 'D')
		return (1);
	if(str[i] == 'x' || str[i] == 'X')
		return (1);
	if(str[i] == 'c' || str[i] == 'C')
		return (1);
	if(str[i] == 'p'|| str[i] == 'i')
		return (1);
	return (0);
}

int is_modifier(char *str, int i)
{
	if(str[i] == 'h' && str[i + 1] != 'h')
		return (1);
	if(str[i] == 'l' && str[i + 1] != 'l')
		return (1);
	if (str[i] == 'l' && str[i + 1] == 'l')
		return (1);
	if (str[i] == 'h' && str[i + 1] == 'h')
		return (1);
	if(str[i] == 'j')
		return (1);
	if(str[i] == 'z')
		return (1);
	return (0);
}