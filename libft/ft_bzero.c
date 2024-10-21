/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:23:41 by aberion           #+#    #+#             */
/*   Updated: 2023/11/13 15:15:26 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

/*
}
int	main(void) {
	char str[50] = "Bonjour tout le monde!";

	printf("Avant ft_bzero: %s\n", str);

	ft_bzero(str, 6);

	printf("Après ft_bzero: ");
	for (size_t i = 0; i < sizeof(str); ++i) {
		putchar(str[i] ? str[i] : ' ');
	}
	putchar('\n');

	return (0);
}
*/