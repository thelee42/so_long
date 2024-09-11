/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:09:46 by thelee            #+#    #+#             */
/*   Updated: 2023/11/30 15:05:26 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"libft.h"

static int	ft_intcount(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;
	int		i;

	num = n;
	i = 0;
	len = ft_intcount(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[i] = '-';
		num *= -1;
		i++;
	}
	str[len] = '\0';
	len -= 1;
	while (len >= i)
	{
		str[len--] = num % 10 + 48;
		num = num / 10;
	}
	return (str);
}
