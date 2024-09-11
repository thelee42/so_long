/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:34:19 by thelee            #+#    #+#             */
/*   Updated: 2023/12/29 15:35:50 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	argptr;
	int		i;
	int		len;

	if (!format)
		return (-1);
	i = 0;
	len = 0;
	va_start(argptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len = len + ft_format(argptr, format[i + 1]);
			i++;
		}
		else
			len = len + ft_print_char(format[i]);
		i++;
	}
	va_end(argptr);
	return (len);
}
