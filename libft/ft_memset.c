/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:51:08 by aberion           #+#    #+#             */
/*   Updated: 2023/11/13 15:33:40 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
	{
		*p++ = (unsigned char)c;
	}
	return (s);
}
/*
int	main(void) {
	char str[50] = "bonjourno";

	printf("Avant memset: %s\n", str);

		ft_memset(str, 'n', 2);

	printf("Après memset: %s\n", str);

	return (0);
}
*/
