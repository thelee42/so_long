/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:55:01 by thelee            #+#    #+#             */
/*   Updated: 2023/12/07 09:28:01 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(unsigned long long p)
{
	int	len;

	if (p == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	len = 2 + ft_print_hexa(p, 'x');
	return (len);
}
