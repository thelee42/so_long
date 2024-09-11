/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:51:01 by thelee            #+#    #+#             */
/*   Updated: 2023/12/07 09:27:24 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list argptr, const char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = len + ft_print_char(va_arg(argptr, int));
	else if (c == 's')
		len = len + ft_print_str(va_arg(argptr, char *));
	else if (c == 'p')
		len = len + ft_print_ptr(va_arg(argptr, unsigned long long));
	else if (c == 'd' || c == 'i')
		len = len + ft_print_nbr(va_arg(argptr, int));
	else if (c == 'u')
		len = len + ft_print_unsigned(va_arg(argptr, unsigned int));
	else if (c == 'x' || c == 'X')
		len = len + ft_print_hexa(va_arg(argptr, unsigned int), c);
	else if (c == '%')
		len = len + ft_print_char('%');
	return (len);
}
