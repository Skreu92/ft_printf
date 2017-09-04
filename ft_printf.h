/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:32:27 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/31 17:33:01 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <sys/types.h>

typedef struct s_flags
{
	int diez;
	int minus;
	int plus;
	int h;
	int l;
	int hh;
	int ll;
	int j;
	int z;
}			t_flags;
typedef struct s_env
{
	char *fmt;
	int len;
	int buff_len;
	int pre;
	t_flags *flags;
}				t_env;
#endif
