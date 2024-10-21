/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:35:31 by aberion           #+#    #+#             */
/*   Updated: 2023/11/28 15:22:56 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_p(unsigned long nbr)
{
	char	*base;
	char	output[16];
	int		i;
	int		len;

	base = "0123456789abcdef";
	i = 15;
	len = 0;
	output[i--] = '\0';
	if (nbr == 0)
		return (ft_putstr("(nil)"));
	while (nbr)
	{
		output[i--] = base[nbr % 16];
		nbr /= 16;
	}
	len = ft_putstr("0x");
	len += ft_putstr(&output[i + 1]);
	return (len);
}
