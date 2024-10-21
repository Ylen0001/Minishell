/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:28:36 by aberion           #+#    #+#             */
/*   Updated: 2023/11/28 17:31:20 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uint(unsigned int n)
{
	int		len;
	int		i;
	char	num[10];

	len = 0;
	i = 10;
	num[i--] = '\0';
	if (n == 0)
		return (ft_putchar('0'));
	while (n)
	{
		num[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (len + ft_putstr(&num[i + 1]));
}
