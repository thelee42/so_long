/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:56:14 by thelee            #+#    #+#             */
/*   Updated: 2023/12/06 19:45:44 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		ft_print_char('-');
		n *= -1;
		len++;
	}
	if (n > 9)
	{
		len = len + ft_print_nbr(n / 10);
		len = len + ft_print_nbr(n % 10);
	}
	else
	{
		ft_print_char(n + 48);
		len++;
	}
	return (len);
}
