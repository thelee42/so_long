/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:14:35 by thelee            #+#    #+#             */
/*   Updated: 2023/12/06 21:44:01 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len = len + ft_print_unsigned(n / 10);
		len = len + ft_print_unsigned(n % 10);
	}
	else
	{
		ft_print_char(n + 48);
		len++;
	}
	return (len);
}
