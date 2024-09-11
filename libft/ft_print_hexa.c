/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:08:53 by thelee            #+#    #+#             */
/*   Updated: 2023/12/06 21:52:01 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa(unsigned long long n, char format)
{
	char	*base;
	int		len;

	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n > 15)
	{
		len = len + ft_print_hexa(n / 16, format);
		len = len + ft_print_hexa(n % 16, format);
	}
	else
	{
		ft_print_char(base[n]);
		len++;
	}
	return (len);
}
