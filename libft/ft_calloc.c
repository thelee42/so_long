/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:08:59 by thelee            #+#    #+#             */
/*   Updated: 2023/11/30 16:29:54 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"libft.h"
/*
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
		return (malloc(0));
	p = (void *)malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count);
	return (p);
}
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	size_total;

	if (!nmemb || !size)
		return (malloc(1));
	if (__SIZE_MAX__ / nmemb < size)
		return (NULL);
	size_total = nmemb * size;
	res = malloc(size_total);
	if (!res)
		return (NULL);
	ft_bzero(res, size_total);
	return (res);
}
