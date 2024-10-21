/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:52:32 by aberion           #+#    #+#             */
/*   Updated: 2023/11/28 15:55:44 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	norminette_killer(int *n, char *num, int *len, int *i)
{
	*len += ft_putchar('-');
	if (*n == -2147483648)
	{
		*n = -(*n / 10);
		num[(*i)--] = '8';
	}
	else
		*n = -*n;
}

int	ft_print_int(int n)
{
	int		len;
	int		i;
	char	num[12];

	len = 0;
	i = 10;
	num[i--] = '\0';
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
		norminette_killer(&n, num, &len, &i);
	while (n)
	{
		num[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (len + ft_putstr(&num[i + 1]));
}
