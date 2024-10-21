/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:49:02 by aberion           #+#    #+#             */
/*   Updated: 2023/11/16 18:14:50 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digit(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*norminette_killer(unsigned int un, char *res, int digit, int n)
{
	if (n < 0)
		res[0] = '-';
	while (un > 0)
	{
		digit--;
		res[digit] = (un % 10) + '0';
		un /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int				digit;
	unsigned int	un;
	char			*res;

	digit = count_digit(n);
	if (n < 0)
	{
		un = -n;
		digit++;
	}
	else
		un = n;
	res = (char *)malloc((sizeof(char) * (digit + 1)));
	if (!res)
		return (NULL);
	res[digit] = 0;
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	return (norminette_killer(un, res, digit, n));
}
