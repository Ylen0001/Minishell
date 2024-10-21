/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:47:42 by aberion           #+#    #+#             */
/*   Updated: 2023/11/28 17:36:12 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, char specifier)
{
	char	*base_lower;
	char	*base_upper;
	int		count;

	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	count = 0;
	if (specifier == 'x')
	{
		if (n >= 16)
			count += ft_print_hex(n / 16, specifier);
		ft_putchar(base_lower[n % 16]);
	}
	else
	{
		if (n >= 16)
			count += ft_print_hex(n / 16, specifier);
		ft_putchar(base_upper[n % 16]);
	}
	return (count + 1);
}
